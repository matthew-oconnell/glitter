#include <string>
#include <utility>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Engine.h"
#include "Input.h"
#include <Shader.h>

using namespace Glitter;
using namespace Core;

Engine::Engine(std::string title, int width, int height)
    : name(std::move(title)),
      window(std::make_shared<Window>(title, width, height)),
      input(std::make_shared<Input>(window->getGLFWHandle())), glew_context(){
  glfwSetWindowUserPointer(window->getGLFWHandle(), (void*)this);
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
  while(!closed()){
    clear();
    Glitter::Core::Input* input = getInput();
    if(input->isKeyPressed(GLFW_KEY_W) || input->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
      glBegin(GL_TRIANGLES);
      float x = input->getCursorX();
      float y = input->getCursorY();
      float width = float(window->getWidth());
      float height = float(window->getHeight());
      float x_percent = x / width;
      float y_percent = -y / height;
      std::cout << "Cusor position " << x << " " << y << " percentages = " << x_percent << " " << y_percent << " width" << width << " height " << height << std::endl;
      x_percent -= 0.5;
      y_percent -= 0.5;
      glVertex2f(-0.1f+x_percent, -0.1f+y_percent);
      glVertex2f( 0.1f+x_percent,  0.1f+y_percent);
      glVertex2f( 0.1f+x_percent, -0.1f+y_percent);
      glEnd();
    }
    update();
  }
}
Window* Engine::getWindow() {
  return window.get();
}
