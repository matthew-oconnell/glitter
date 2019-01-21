#include <string>
#include <random>
#include <utility>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Game.h"
#include "GLFWInput.h"
#include <Shader.h>
#include <cmath>
#include <Enemy.h>
#include <AABB.h>
#include <Texture.h>
#include <FPSCounter.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Glitter;
using namespace Core;

Game::Game(std::string title)
    : name(std::move(title)),
      engine(){
  game_start = std::chrono::system_clock::now();
  float pixels_per_meter = 90.0f;
  engine.getCamera()->setPixelsPerMeter(pixels_per_meter);
  auto [width, height] = engine.getWindow()->getWidthAndHeight();
  engine.getCamera()->windowResize(width, height);

  auto shoot = [this](std::shared_ptr<Player::Bullet> b){
    bullets.emplace_back(b);
  };
  auto player_one = std::make_shared<Glitter::Player::Ally>(engine.getModelDatabase(),engine.getInput(), engine.getCamera(), shoot);
  std::cout << "Trying to create player one." << std::endl;
  player_one->setModel(std::make_shared<Glitter::Graphics::Texture>(engine.getModelDatabase(),"assets/textures/ufo.png", 1.0f, 1.0f));
  player_one->setWorldLocation({5.0f, 5.0f});
  addAlly(player_one);
}
template <typename Killable>
void eraseDead(std::vector<std::shared_ptr<Killable>>& killables){
  for(auto iter = killables.begin(); iter != killables.end();) {
    auto* e = iter->get();
    if(!e->isAlive()){
      iter = killables.erase(iter);
    } else {
      ++iter;
    }
  }
}

void Game::update() {
  for(auto& e : enemies)
    e->update();
  for(auto& p : allies)
    p->update();
  for(auto b_iter = bullets.begin(); b_iter != bullets.end();){
    auto& b = *b_iter;
    b->update();
    auto [lo, hi] = b->getBoundsWorld();
    if(!engine.getCamera()->onScreen(lo, hi))
      b_iter = bullets.erase(b_iter);
    else
      ++b_iter;
  }
  engine.getWindow()->update();
}
bool Game::closed() {
  return engine.getWindow()->closed();
}
void Game::clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Game::loop() {

  Graphics::Shader text_shader("assets/shaders/text.vert", "assets/shaders/text.frag");
  auto [width, height] = engine.getWindow()->getWidthAndHeight();
  glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width), 0.0f,
                                    static_cast<GLfloat>(height));
  glUniformMatrix4fv(glGetUniformLocation(text_shader.getId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

  Utilities::FPSCounter fps_counter;
  unsigned int game_frame_count = 0;
  while(!closed()){
    auto now = std::chrono::system_clock::now();
    auto game_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - game_start);
    if(game_frame_count % 10 == 0)
      setScreenColorBlack();
    update();
    spawnEnemies(game_time);
    spawnPowerUps(game_time);
    collideBulletsWithEnemies();
    collidePlayersWithEnemies();
    collidePlayersWithPowerUps();
    eraseDead(bullets);
    eraseDead(enemies);
    eraseDead(power_ups);
    render();
    game_frame_count++;
    fps_counter.frame();
    if(score > high_score)
      high_score = score;
    std::string score_string = std::to_string(score);
    std::string high_score_string = std::to_string(high_score);
    text.renderText(text_shader,"Score: " + score_string + "  High Score: " + high_score_string, 100.0f, 25.0f, 1.0f, {0.9f,0.8f,0.2f,1.0f});

//    std::string fps_string(std::to_string(int(std::ceil(fps_counter.fps()))));
//    text.renderText(text_shader,"FPS: " + fps_string, 900.0f, 25.0f, 0.5f, {0.5f,0.8f,0.2f,1.0f});
  }
}
void Game::addAlly(std::shared_ptr<Player::Ally> p) {
    allies.emplace_back(std::move(p));
}
void Game::spawnEnemies(std::chrono::milliseconds game_time) {
  double spawn_rate_in_seconds = 1.0;
  static std::chrono::milliseconds last_enemy_spawned;
  auto elapsed_time_since_last_enemy_in_seconds = (game_time.count() - last_enemy_spawned.count()) / 1000.0;
  if(elapsed_time_since_last_enemy_in_seconds > spawn_rate_in_seconds) {
    spawnRandomEnemy();
    last_enemy_spawned = game_time;
  }
}
void Game::spawnPowerUps(std::chrono::milliseconds game_time) {
  double spawn_rate_in_seconds = 5.0;
  static std::chrono::milliseconds last_spawned;
  auto elapsed_time_since_last_spawned = (game_time.count() - last_spawned.count()) / 1000.0;
  if(elapsed_time_since_last_spawned > spawn_rate_in_seconds) {
    auto power_up = std::make_shared<Player::PowerUp>(engine.getModelDatabase(), Math::Vec2d{10.0f,10.0f});
    auto model = std::make_shared<Graphics::Texture>(engine.getModelDatabase(), "assets/textures/bullet.png", 1.0f, 1.0f);
    power_up->setModel(model);
    power_ups.push_back(power_up);
    last_spawned = game_time;
  }
}
void Game::spawnRandomEnemy() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  auto enemy = std::make_shared<Player::Enemy>(engine.getCamera());
  enemy->setHealth(2);
  enemy->setModel(std::make_shared<Graphics::Texture>(engine.getModelDatabase(),"assets/textures/enemy.png", 0.4f, 0.4f));
  auto [lo, hi] = engine.getCamera()->rangeInWorldCoordinates();
  std::uniform_real_distribution y_distribution(lo.y, hi.y);
  auto spawn_location = Math::Vec2d{hi.x, float(y_distribution(gen))};
  enemy->setWorldLocation(spawn_location);
  enemy->setTarget(allies.front().get());
  addEnemy(enemy);
}
void Game::addEnemy(std::shared_ptr<Player::Enemy> e) {
  enemies.emplace_back(e);
}
void Game::collidePlayersWithEnemies() {
  for(auto& p : allies) {
    for (auto &e : enemies) {
      if(e->isAlive()) {
        if (collide(p.get(), e.get())) {
          e->die();
          playerDies(p.get());
        }
      }
    }
  }
}
bool Game::collide(Player::Player *p, Player::Player *e) {
  auto p_bounds = p->getBoundsWorld();
  auto e_bounds = e->getBoundsWorld();
  return Math::AABB::intersect(e_bounds, p_bounds);
}
void Game::render() {
  clear();
  drawEnemies();
  drawBullets();
  drawPlayers();
  drawPowerUps();
}
void Game::drawPlayers() {
  for(auto& p : allies){
    auto [lo, hi] = p->getBoundsWorld();
    if(engine.getCamera()->onScreen(lo, hi)) {
      p->render(engine.getCamera());
    }
  }
}
void Game::drawBullets() {
  for(auto& b : bullets){
    auto [lo, hi] = b->getBoundsWorld();
    if(engine.getCamera()->onScreen(lo, hi)) {
      b->render(engine.getCamera());
    }
  }
}
void Game::drawEnemies() {
  for(auto& e : enemies){
    auto [lo, hi] = e->getBoundsWorld();
    if(engine.getCamera()->onScreen(lo, hi))
      e->render(engine.getCamera());
  }
}
void Game::drawPowerUps() {
  for(auto& u : power_ups){
    auto [lo, hi] = u->getBoundsWorld();
    if(engine.getCamera()->onScreen(lo, hi))
      u->render(engine.getCamera());
  }
}

void Game::collideBulletsWithEnemies() {
  for(auto& b : bullets){
    auto bullet_bounds = b->getBoundsWorld();
    for(auto& e : enemies){
      auto enemy_bounds = e->getBoundsWorld();
      if(Math::AABB::intersect(enemy_bounds, bullet_bounds)){
        if(e->isAlive()) {
          b->explode();
          e->takeDamage(b->damage());
          score += 10;
          break;
        }
      }
    }
  }
}

void Game::collidePlayersWithPowerUps() {
  for(auto& a : allies){
    for(auto& u : power_ups){
      if(Math::AABB::intersect(a->getBoundsWorld(), u->getBoundsWorld())){
        u->powerUp(a.get(),
            [this](std::shared_ptr<Player::Bullet> b){bullets.push_back(b);});
        u->consume();
      }
    }
  }
}
void Game::flashScreenRed() {
  glClearColor(0.7f, 0.2f, 0.2f, 0.5f);
}
void Game::setScreenColorBlack() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
void Game::playerDies(Player::Ally* p) {
  p->setWorldLocation({4.0f, 4.0f});
  flashScreenRed();
  clearAllEnemies();
  clearAllPowerUps();
  score = 0;
  auto w = std::make_shared<Player::SingleShooter>(engine.getModelDatabase());
  w->putBulletsHere([this](std::shared_ptr<Player::Bullet> b){bullets.push_back(b);});
  p->equipWeapon(w);
}
void Game::clearAllEnemies() {
  for(auto& e : enemies){
    e->die();
  }
}
void Game::clearAllPowerUps() {
  for(auto& p : power_ups){
    p->consume();
  }
}
Engine* Game::getEngine() {
  return &engine;
}
