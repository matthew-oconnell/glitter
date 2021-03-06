#include <stdio.h>
#include "Window.h"
#include "Game.h"
using namespace Glitter;

Window::~Window() {
  glfwDestroyWindow(window_handle);
}
Window::Window(Camera* screen, std::string title)
    : screen(screen), title(title){

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  auto monitor = glfwGetPrimaryMonitor();
  auto mode = glfwGetVideoMode(monitor);
  width = mode->width;
  height = mode->height;
  monitor = nullptr; // disable fullscreen
  width = int(width / 1.5);
  height = int(height /1.5);
  window_handle = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);
  if(window_handle == nullptr)
    throw std::logic_error("Could not create glfw window: " + title);

  glfwMakeContextCurrent(window_handle);
  glfwSetWindowSizeCallback(window_handle, window_resize_callback);
  glfwSetInputMode(window_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::window_resize_callback(GLFWwindow *window, int width, int height) {
  auto w = static_cast<Core::Game*>(glfwGetWindowUserPointer(window))->getEngine()->getWindow();
  w->width = width;
  w->height = height;
  w->screen->windowResize(width, height);
  glViewport(0, 0, width, height);
}
GLFWwindow *Window::getGLFWHandle() {
  return window_handle;
}
void Window::update() {
  glfwSwapBuffers(window_handle);
  glfwPollEvents();
}
bool Window::closed() {
  return bool(glfwWindowShouldClose(window_handle));
}
std::array<int, 2> Window::getWidthAndHeight() {
  return {width, height};
}
