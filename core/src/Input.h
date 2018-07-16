#pragma once
#include <array>
#include <GLFW/glfw3.h>

namespace Glitter{
namespace Core {
class Input {
 public:
  Input(GLFWwindow* window);
  bool isKeyPressed(unsigned int key_code) const;
  bool isMouseButtonPressed(unsigned int button_code) const;
  float getCursorX() const;
  float getCursorY() const;

 private:
  const static int MAX_KEYBOARD_KEYS = 1024;
  const static int MAX_MOUSE_BUTTONS = 32;
  GLFWwindow* window;
  std::array<bool, MAX_KEYBOARD_KEYS> keyboard_keys;
  std::array<bool, MAX_MOUSE_BUTTONS> mouse_buttons;
  float mouse_x, mouse_y;

  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void cursor_position_callback(GLFWwindow* window, double x, double y);
  static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};
}
}

