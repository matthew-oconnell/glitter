#include "GLFWInput.h"
#include "Game.h"
using namespace Glitter;

GLFWInput::GLFWInput(GLFWwindow *window)
: window(window){
  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetCursorPosCallback(window, cursor_position_callback);
  for (bool &keyboard_key : keyboard_keys)
    keyboard_key = false;

  for (bool &mouse_button : mouse_buttons)
    mouse_button = false;
}
void GLFWInput::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  auto input = static_cast<Engine*>(glfwGetWindowUserPointer(window))->getInput();
  if(action == GLFW_PRESS)
    input->keyboard_keys[key] = true;
  else if(action == GLFW_RELEASE)
    input->keyboard_keys[key] = false;
}
void GLFWInput::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
  auto input = static_cast<Engine*>(glfwGetWindowUserPointer(window))->getInput();
  if(action == GLFW_PRESS)
    input->mouse_buttons[button] = true;
  else if(action == GLFW_RELEASE)
    input->mouse_buttons[button] = false;
}
void GLFWInput::cursor_position_callback(GLFWwindow *window, double x, double y) {
  auto input = static_cast<Engine*>(glfwGetWindowUserPointer(window))->getInput();
  input->mouse_x = (float)x;
  input->mouse_y = (float)y;
}
unsigned int GLFWInput::mapToGLFWKeycode(Player::Input::KEYS k) const {
  if(k == Player::Input::KEYS::W)
    return GLFW_KEY_W;
  if(k == Player::Input::KEYS::A)
    return GLFW_KEY_A;
  if(k == Player::Input::KEYS::S)
    return GLFW_KEY_S;
  if(k == Player::Input::KEYS::D)
    return GLFW_KEY_D;
  if(k == Player::Input::KEYS::SPACE)
    return GLFW_KEY_SPACE;
  return MAX_KEYBOARD_KEYS+1;
}
bool GLFWInput::pressed(Player::Input::KEYS k) const {
  unsigned int keycode = mapToGLFWKeycode(k);
  if(keycode > MAX_KEYBOARD_KEYS)
    return false;
  return keyboard_keys[keycode];
}
bool GLFWInput::isMouseButtonPressed(unsigned int button_code) const {
  if(button_code > MAX_MOUSE_BUTTONS)
    return false;
  return mouse_buttons[button_code];
}
Math::Vec2d GLFWInput::getCursorLocation() const {
  return {mouse_x, mouse_y};
}
