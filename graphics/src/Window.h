#pragma once
#include <string>
#include <array>
struct GLFWwindow;

namespace Glitter {
namespace Graphics {
class Window {
  const static int MAX_KEYBOARD_KEYS = 1024;
  const static int MAX_MOUSE_BUTTONS = 32;

 public:
  Window(std::string title, int width, int height);
  void update();
  bool closed();
  bool isKeyPressed(unsigned int key_code) const;
  bool isMouseButtonPressed(unsigned int button_code) const;
  float getCursorX() const;
  float getCursorY() const;
  int getWidth() const;
  int getHeight() const;
  ~Window();
  void clear();
 private:
  std::string name;
  GLFWwindow *window_handle;
  int width, height;
  std::array<bool, MAX_KEYBOARD_KEYS> keyboard_keys;
  std::array<bool, MAX_MOUSE_BUTTONS> mouse_buttons;
  float mouse_x, mouse_y;

  //GLFW callback methods
  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void cursor_position_callback(GLFWwindow* window, double x, double y);
  static void window_resize_callback(GLFWwindow* window, int width, int height);
  static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};
}
}


