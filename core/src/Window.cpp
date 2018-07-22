#include "Window.h"
#include "Engine.h"
using namespace Glitter;
using namespace Core;

Window::~Window() {
  glfwDestroyWindow(window_handle);
}
Window::Window(Screen* screen, std::string title, int width, int height)
    : screen(screen), title(title), width(width), height(height){

  window_handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if(window_handle == nullptr)
    throw std::logic_error("Could not create some glfw window: " + title);

  glfwMakeContextCurrent(window_handle);
  glfwSetWindowSizeCallback(window_handle, window_resize_callback);
  glfwSetInputMode(window_handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Window::window_resize_callback(GLFWwindow *window, int width, int height) {
  auto w = static_cast<Engine*>(glfwGetWindowUserPointer(window))->getWindow();
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
int Window::getHeight() {
  return height;
}
int Window::getWidth() {
  return width;
}
