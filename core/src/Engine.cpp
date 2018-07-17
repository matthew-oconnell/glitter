#include <string>
#include <utility>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Engine.h"
#include "Input.h"
#include <Shader.h>
#include <Square.h>
#include <cmath>

using namespace Glitter;
using namespace Core;

Engine::Engine(std::string title, int width, int height)
    : name(std::move(title)),
      screen(),
      window(std::make_shared<Window>(&screen, title, width, height)),
      input(std::make_shared<Input>(window->getGLFWHandle())),
      glew_context(){
  glfwSetWindowUserPointer(window->getGLFWHandle(), (void*)this);
  game_start = std::chrono::system_clock::now();
  screen.setWorldLocationRange({0.0f, 0.0f}, {float(width), float(height)});
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
Input* Engine::getInput() {
  return input.get();
}
void Engine::loop() {
  float pi = 4.0f*atan(1.0f);
  float frequency = 0.2f; // 1 rotation per second.

  while(!closed()){
    auto now = std::chrono::system_clock::now();
    auto game_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - game_start).count();
    clear();
    Glitter::Core::Input* input = getInput();
    if(! (input->isKeyPressed(GLFW_KEY_W) || input->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))) {
      drawStupiderCursor();
    }
    for(auto& p : players){
      float game_time_in_seconds = float(game_time)/1000.0f;
      auto loc = Math::Vec2d{1.0f, 1.0f}*0.5f*std::cos(2.0f*pi*frequency*game_time_in_seconds);
      p->setWorldLocation(loc);
      auto model = p->getModel();
      auto [lo, hi] = model->getBounds();
      if(screen.onScreen(lo, hi))
        p->render(p->getWorldLocation());
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
  float x_percent = (2.0f*x / width) - 1.0f;
  float y_percent = -(2.0f*y / height) + 1.0f;
  glVertex2f( 0.0f+x_percent,  0.0f+y_percent);
  glVertex2f(-0.02f+x_percent, -0.1f+y_percent);
  glVertex2f( 0.02f+x_percent, -0.1f+y_percent);
  glEnd();
}
void Engine::addPlayer(std::shared_ptr<Player::Player> p) {
    players.emplace_back(std::move(p));
}
