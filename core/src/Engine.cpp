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
  float pixels_per_meter = 40.0f;
  screen.setScreenScale(pixels_per_meter);
  screen.windowResize(window->getWidth(), window->getHeight());
}
void Engine::update() {
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

  while(!closed()){
    auto now = std::chrono::system_clock::now();
    auto game_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - game_start);
    spawnEnemies(game_time);
    clear();
    Glitter::Core::GLFWInput* input = getInput();
    if(!input->pressed(Player::Input::KEYS::W))
      drawStupiderCursor();
    for(auto& p : players){
      auto model = p->getModel();
      auto [lo, hi] = model->getBounds();
      if(screen.onScreen(lo, hi)) {
        p->update();
        p->render(&screen);
      }
    }
    update();
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
  enemy->setModel(std::make_shared<Graphics::Square>(0.6f, 0.6f));
  auto [lo, hi] = screen.rangeInWorldCoordinates();
  std::uniform_real_distribution x_distribution(lo.x, hi.x);
  std::uniform_real_distribution y_distribution(lo.y, hi.y);
  auto spawn_location = Math::Vec2d{float(x_distribution(gen)), float(y_distribution(gen))};
  enemy->setWorldLocation(spawn_location);
  addPlayer(enemy);
}
