#include "Input.h"
#include "Engine.h"
using namespace Glitter;
using namespace Core;

Input::Input(GLFWwindow *window) : window(window){
  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetCursorPosCallback(window, cursor_position_callback);
  for (bool &keyboard_key : keyboard_keys)
    keyboard_key = false;

  for (bool &mouse_button : mouse_buttons)
    mouse_button = false;
}

void Input::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  auto input = static_cast<Engine*>(glfwGetWindowUserPointer(window))->getInput();
  if(action == GLFW_PRESS)
    input->keyboard_keys[key] = true;
  else if(action == GLFW_RELEASE)
    input->keyboard_keys[key] = false;
}
void Input::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
  auto input = static_cast<Engine*>(glfwGetWindowUserPointer(window))->getInput();
  if(action == GLFW_PRESS)
    input->mouse_buttons[button] = true;
  else if(action == GLFW_RELEASE)
    input->mouse_buttons[button] = false;
}
void Input::cursor_position_callback(GLFWwindow *window, double x, double y) {
  auto input = static_cast<Engine*>(glfwGetWindowUserPointer(window))->getInput();
  input->mouse_x = (float)x;
  input->mouse_y = (float)y;
}
bool Input::isKeyPressed(unsigned int keycode) const {
  if(keycode > MAX_KEYBOARD_KEYS)
    return false;
  return keyboard_keys[keycode];
}
bool Input::isMouseButtonPressed(unsigned int button_code) const {
  if(button_code > MAX_MOUSE_BUTTONS)
    return false;
  return mouse_buttons[button_code];
}
float Input::getCursorX() const {
  return mouse_x;
}
float Input::getCursorY() const {
  return mouse_y;
}
