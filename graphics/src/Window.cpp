#include <string>
#include <utility>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Window.h"

using namespace Glitter;
using namespace Graphics;

Window::Window(std::string title, int width, int height)
    : name(std::move(title)), window_handle(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr)){
  if(window_handle == nullptr)
    throw std::logic_error("Could not create some glfw window: " + title);
  glfwMakeContextCurrent(window_handle);
  glfwSetWindowSizeCallback(window_handle, window_resize_callback);
  glfwSetKeyCallback(window_handle, key_callback);
  glfwSetCursorPosCallback(window_handle, cursor_position_callback);
  glfwSetWindowUserPointer(window_handle, (void*)this);
  for (bool &keyboard_key : keyboard_keys)
    keyboard_key = false;

  for (bool &mouse_button : mouse_buttons)
    mouse_button = false;

  if( glewInit() != GLEW_OK){
    std::cout<<"could not initialize glew" << std::endl;
    exit(1);
  }
  std::cout << "OpeGL " << glGetString(GL_VERSION) << std::endl;
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
void Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  auto my_window = static_cast<Window*>(glfwGetWindowUserPointer(window));
  if(action == GLFW_PRESS)
    my_window->keyboard_keys[key] = true;
  else if(action == GLFW_RELEASE)
    my_window->keyboard_keys[key] = false;
}
void Window::cursor_position_callback(GLFWwindow *window, double x, double y) {
  auto my_window = static_cast<Window*>(glfwGetWindowUserPointer(window));
}
void Window::window_resize_callback(GLFWwindow *window, int width, int height) {
  auto my_window = static_cast<Window*>(glfwGetWindowUserPointer(window));
  glViewport(0, 0, width, height);
}
bool Window::isKeyPressed(unsigned int keycode) const {
  if(keycode > MAX_KEYBOARD_KEYS)
    return false;
  return keyboard_keys[keycode];
}
bool Window::isMouseButtonPressed(unsigned int button_code) const {
  if(button_code > MAX_MOUSE_BUTTONS)
    return false;
  return mouse_buttons[button_code];
}
