#include <string>
#include <random>
#include <utility>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Engine.h"
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

Engine::Engine(std::string title)
    : name(std::move(title)),
      screen(),
      window(std::make_shared<Window>(&screen, name)),
      glew_context(),
      input(std::make_shared<GLFWInput>(window->getGLFWHandle())){
  glfwSetWindowUserPointer(window->getGLFWHandle(), (void*)this);
  game_start = std::chrono::system_clock::now();
  float pixels_per_meter = 90.0f;
  screen.setPixelsPerMeter(pixels_per_meter);
  auto [width, height] = window->getWidthAndHeight();
  screen.windowResize(width, height);

  auto shoot = [this](std::shared_ptr<Player::Bullet> b){
    bullets.emplace_back(b);
  };
  auto player_one = std::make_shared<Glitter::Player::Ally>(resource_manager,getInput(), getScreen(), shoot);
  std::cout << "Trying to create player one." << std::endl;
  player_one->setModel(std::make_shared<Glitter::Graphics::Texture>(resource_manager,"assets/ufo.png", 1.0f, 1.0f));
  player_one->setWorldLocation({5.0f, 5.0f});
  addAlly(player_one);
}
void Engine::update() {
  for(auto& e : enemies)
    e->update();
  for(auto& p : allies)
    p->update();
  for(auto b_iter = bullets.begin(); b_iter != bullets.end();){
    auto& b = *b_iter;
    b->update();
    auto [lo, hi] = b->getBoundsWorld();
    if(!screen.onScreen(lo, hi))
      b_iter = bullets.erase(b_iter);
    else
      ++b_iter;
  }
  window->update();
}
bool Engine::closed() {
  return window->closed();
}
void Engine::clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
GLFWInput* Engine::getInput() {
  return input.get();
}
void Engine::loop() {

  Graphics::Shader text_shader("assets/shaders/text.vert", "assets/shaders/text.frag");
  auto [width, height] = window->getWidthAndHeight();
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
    collideBulletsWithEnemies();
    collidePlayersWithEnemies();
    render();
    game_frame_count++;
    fps_counter.frame();
    std::string fps_string = std::to_string(fps_counter.fps());
    text.renderText(text_shader,"FPS: " + fps_string, 100.0f, 25.0f, 1.0f, {0.5f,0.8f,0.2f,1.0f});
  }
}
Window* Engine::getWindow() {
  return window.get();
}
void Engine::addAlly(std::shared_ptr<Player::Ally> p) {
    allies.emplace_back(std::move(p));
}
void Engine::spawnEnemies(std::chrono::milliseconds game_time) {
  double spawn_rate_in_seconds = 1.0;
  static std::chrono::milliseconds last_enemy_spawned;
  auto elapsed_time_since_last_enemy_in_seconds = (game_time.count() - last_enemy_spawned.count()) / 1000.0;
  if(elapsed_time_since_last_enemy_in_seconds > spawn_rate_in_seconds) {
    spawnRandomEnemy();
    last_enemy_spawned = game_time;
  }
}
void Engine::spawnRandomEnemy() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  auto enemy = std::make_shared<Player::Enemy>(&screen);
  enemy->setModel(std::make_shared<Graphics::Texture>(resource_manager,"assets/enemy.png", 0.4f, 0.4f));
  auto [lo, hi] = screen.rangeInWorldCoordinates();
  std::uniform_real_distribution y_distribution(lo.y, hi.y);
  auto spawn_location = Math::Vec2d{hi.x, float(y_distribution(gen))};
  enemy->setWorldLocation(spawn_location);
  enemy->setTarget(allies.front().get());
  addEnemy(enemy);
}
void Engine::addEnemy(std::shared_ptr<Player::Enemy> e) {
  enemies.emplace_back(e);
}
void Engine::collidePlayersWithEnemies() {
  for(auto& p : allies){
    for(auto e_iter = enemies.begin(); e_iter != enemies.end();){
      if(collide(p.get(), e_iter->get())){
        playerDies(p.get());
        return;
      } else {
        ++e_iter;
      }
    }
  }
}
bool Engine::collide(Player::Player *p, Player::Player *e) {
  auto p_bounds = p->getBoundsWorld();
  auto e_bounds = e->getBoundsWorld();
  return Math::AABB::intersect(e_bounds, p_bounds);
}
void Engine::render() {
  clear();
  drawEnemies();
  drawBullets();
  drawPlayers();
}
void Engine::drawPlayers() {
  for(auto& p : allies){
    auto [lo, hi] = p->getBoundsWorld();
    if(screen.onScreen(lo, hi)) {
      p->render(&screen);
    }
  }
}
void Engine::drawBullets() {
  for(auto& b : bullets){
    auto [lo, hi] = b->getBoundsWorld();
    if(screen.onScreen(lo, hi)) {
      b->render(&screen);
    }
  }
}
void Engine::drawEnemies() {
  for(auto& e : enemies){
    auto [lo, hi] = e->getBoundsWorld();
    if(screen.onScreen(lo, hi))
      e->render(&screen);
  }
}
Screen* Engine::getScreen() {
  return &screen;
}
void Engine::collideBulletsWithEnemies() {
  for(auto b_iter = bullets.begin(); b_iter != bullets.end();){
    auto &b = *b_iter;
    auto bullet_bounds = b->getBoundsWorld();
    for(auto e_iter = enemies.begin(); e_iter != enemies.end();){
      auto& e = *e_iter;
      auto enemy_bounds = e->getBoundsWorld();
      if(Math::AABB::intersect(enemy_bounds, bullet_bounds)){
        e_iter = enemies.erase(e_iter);
        b_iter = bullets.erase(b_iter);
        break;
      } else {
        ++e_iter;
      }
    }
    ++b_iter;
  }
}
void Engine::flashScreenRed() {
  glClearColor(0.7f, 0.2f, 0.2f, 0.5f);
}
void Engine::setScreenColorBlack() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
void Engine::playerDies(Player::Ally* p) {
  p->setWorldLocation({4.0f, 4.0f});
  flashScreenRed();
  resetEnemies();
}
void Engine::resetEnemies() {
  enemies.clear();
}
