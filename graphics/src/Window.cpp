#include <string>
#include <utility>
#include <GLFW/glfw3.h>
#include "Window.h"

using namespace Glitter;
using namespace Graphics;


void windowResize(GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
}
Window::Window(std::string title, int width, int height)
    : name(std::move(title)), window_handle(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr)) {
  if(window_handle == nullptr)
    throw std::logic_error("Could not create some glfw window: " + title);
  glfwMakeContextCurrent(window_handle);
  glfwSetWindowSizeCallback(window_handle, windowResize);
}
Window::~Window() {
  glfwDestroyWindow(window_handle);
}
void Window::update() {
  glfwSwapBuffers(window_handle);
  glfwPollEvents();
}
bool Window::closed() {
  return bool(glfwWindowShouldClose(window_handle));
}
void Window::clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}