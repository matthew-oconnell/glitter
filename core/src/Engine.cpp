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
  screen.setScreenScale(pixels_per_meter);
  screen.windowResize(window->getWidth(), window->getHeight());
}
void Engine::update() {
  window->update();
  for(auto& e : enemies)
    e->update();
  for(auto& p : players)
    p->update();
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

  while(!closed()){
    auto now = std::chrono::system_clock::now();
    auto game_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - game_start);
    update();
    spawnEnemies(game_time);
    collidePlayersWithEnemies();
    clear();
    render();
  }
}
Window* Engine::getWindow() {
  return window.get();
}

void Engine::drawStupiderCursor(){
  // This method draws a little triangle at the cursor.
  // Because the cursor is chasing you.
  // You have been warned.
  glBegin(GL_TRIANGLES);
  float x = input->getCursorX();
  float y = input->getCursorY();
  float width = float(window->getWidth());
  float height = float(window->getHeight());
  float x_percent = x / width;
  float y_percent = y / height;
  float screen_x = (2.0f*x_percent) - 1.0f;
  float screen_y = -(2.0f*y_percent) + 1.0f;
  glVertex2f( 0.0f+screen_x,  0.0f+screen_y);
  glVertex2f(-0.02f+screen_x, -0.1f+screen_y);
  glVertex2f( 0.02f+screen_x, -0.1f+screen_y);
  glEnd();
}
void Engine::addPlayer(std::shared_ptr<Player::Player> p) {
    players.emplace_back(std::move(p));
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
  for(auto& p : players){
    for(auto e_iter = enemies.begin(); e_iter != enemies.end();){
      if(collide(p.get(), e_iter->get())){
        e_iter = enemies.erase(e_iter);
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
  Glitter::Core::GLFWInput* input = getInput();
  if(!input->pressed(Player::Input::KEYS::W))
    drawStupiderCursor();
}
void Engine::render() {
//  drawCursor();
  for(auto& e : enemies){
    auto [lo, hi] = e->getBoundsWorld();
    if(screen.onScreen(lo, hi))
      e->render(&screen);
  }
  for(auto& p : players){
    auto [lo, hi] = p->getBoundsWorld();
    if(screen.onScreen(lo, hi)) {
      p->render(&screen);
    }
  }
}
