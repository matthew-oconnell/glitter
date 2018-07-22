#include <string>
#include <random>
#include <utility>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Engine.h"
#include "GLFWInput.h"
#include <Shader.h>
#include <Square.h>
#include <cmath>
#include <Map.h>
#include <Enemy.h>
#include <AABB.h>
#include <Line.h>

using namespace Glitter;
using namespace Core;

Engine::Engine(std::string title, int width, int height)
    : name(std::move(title)),
      screen(),
      window(std::make_shared<Window>(&screen, title, width, height)),
      input(std::make_shared<GLFWInput>(window->getGLFWHandle())),
      glew_context(){
  glfwSetWindowUserPointer(window->getGLFWHandle(), (void*)this);
  game_start = std::chrono::system_clock::now();
  float pixels_per_meter = 90.0f;
  screen.setPixelsPerMeter(pixels_per_meter);
  screen.windowResize(window->getWidth(), window->getHeight());

  auto shoot = [this](std::shared_ptr<Player::Bullet> b){
    bullets.emplace_back(b);
  };
  auto player_one = std::make_shared<Glitter::Player::Ally>(getInput(), getScreen(), shoot);
  player_one->setModel(std::make_shared<Glitter::Graphics::Square>(1.0f, 1.0f, std::array<GLfloat, 4>{0.8f, 0.3f, 0.3f, 1.0f}));
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

  unsigned int game_frame_count = 0;
  while(!closed()){
    auto now = std::chrono::system_clock::now();
    auto game_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - game_start);
    if(game_frame_count % 10 == 0)
      setScreenColorBlue();
    update();
    spawnEnemies(game_time);
    collideBulletsWithEnemies();
    collidePlayersWithEnemies();
    render();
    game_frame_count++;
    std::cout << "total frames: " << game_frame_count << " FPS: " << game_frame_count/(game_time.count()/1000.0) << std::endl;
  }
}
Window* Engine::getWindow() {
  return window.get();
}
void Engine::addAlly(std::shared_ptr<Player::Ally> p) {
    allies.emplace_back(std::move(p));
}
void Engine::spawnEnemies(std::chrono::milliseconds game_time) {
  double spawn_rate_in_seconds = 2.0;
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
  auto enemy = std::make_shared<Player::Enemy>();
  std::uniform_real_distribution color_distribution(0.0, 1.0);
  std::array<GLfloat, 4> color={float(color_distribution(gen)),
                                float(color_distribution(gen)),
                                float(color_distribution(gen)), 1.0f};
  enemy->setModel(std::make_shared<Graphics::Square>(0.6f, 0.6f, color));
  auto [lo, hi] = screen.rangeInWorldCoordinates();
  std::uniform_real_distribution x_distribution(lo.x, hi.x);
  std::uniform_real_distribution y_distribution(lo.y, hi.y);
  auto spawn_location = Math::Vec2d{float(x_distribution(gen)), float(y_distribution(gen))};
  enemy->setWorldLocation(spawn_location);
  addEnemy(enemy);
}
void Engine::addEnemy(std::shared_ptr<Player::Enemy> e) {
  enemies.emplace_back(e);
}
void Engine::collidePlayersWithEnemies() {
  for(auto& p : allies){
    for(auto e_iter = enemies.begin(); e_iter != enemies.end();){
      if(collide(p.get(), e_iter->get())){
        e_iter = enemies.erase(e_iter);
        flashScreenRed();
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
void Engine::drawCursor() {
  glBegin(GL_TRIANGLES);
  auto screen_coords = input->getCursorLocation();
  auto world_coords = screen.convertScreenToWorld(screen_coords);
  auto render_coords = screen.convertWorldToRender(world_coords);
  glVertex2f( 0.00f+render_coords.x,  0.0f+render_coords.y);
  glVertex2f(-0.02f+render_coords.x, -0.1f+render_coords.y);
  glVertex2f( 0.02f+render_coords.x, -0.1f+render_coords.y);
  glEnd();
}
void Engine::render() {
  clear();
//  drawCursor();
  drawAim();
  for(auto& e : enemies){
    auto [lo, hi] = e->getBoundsWorld();
    if(screen.onScreen(lo, hi))
      e->render(&screen);
  }
  for(auto& p : allies){
    auto [lo, hi] = p->getBoundsWorld();
    if(screen.onScreen(lo, hi)) {
      p->render(&screen);
    }
  }
  for(auto& b : bullets){
    auto [lo, hi] = b->getBoundsWorld();
    if(screen.onScreen(lo, hi)) {
      b->render(&screen);
    }
  }
}
Screen* Engine::getScreen() {
  return &screen;
}
void Engine::drawAim() {
  auto player_location = allies.front()->getWorldLocation();
  auto cursor_location = screen.convertScreenToWorld(input->getCursorLocation());
  auto line = Graphics::Line(player_location, cursor_location);
  line.render({0.0f, 0.0f}, &screen);
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
void Engine::setScreenColorBlue() {
  glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
}
