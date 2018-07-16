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
      window_handle(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr)),
      width(width), height(height){
  if(window_handle == nullptr)
    throw std::logic_error("Could not create some glfw window: " + title);
  glfwMakeContextCurrent(window_handle);
  glfwSetWindowSizeCallback(window_handle, window_resize_callback);
  glfwSetWindowUserPointer(window_handle, (void*)this);
  if( glewInit() != GLEW_OK){
    std::cout<<"could not initialize glew" << std::endl;
    exit(1);
  }
  input = std::make_shared<Input>(window_handle);
}
Engine::~Engine() {
  glfwDestroyWindow(window_handle);
}
int Engine::getWidth() const {
  return width;
}
int Engine::getHeight() const {
  return height;
}
void Engine::update() {
  glfwSwapBuffers(window_handle);
  glfwPollEvents();
}
bool Engine::closed() {
  return bool(glfwWindowShouldClose(window_handle));
}
void Engine::clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Engine::window_resize_callback(GLFWwindow *window, int width, int height) {
  auto my_window = static_cast<Engine*>(glfwGetWindowUserPointer(window));
  my_window->width = width;
  my_window->height = height;
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
      float width = float(getWidth());
      float height = float(getHeight());
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
