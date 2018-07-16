#include <string>
#include <utility>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Engine.h"
#include "Input.h"

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
  std::cout << "OpeGL " << glGetString(GL_VERSION) << std::endl;
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
