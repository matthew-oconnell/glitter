#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Screen.h>
namespace Glitter {
namespace Core {
class Window {
 public:
  Window(Screen * screen, std::string title);
  ~Window();
  GLFWwindow* getGLFWHandle();
  void update();
  bool closed();
  std::array<int, 2> getWidthAndHeight();
 private:
  std::string title;
  int width;
  int height;
  GLFWwindow *window_handle;
  Screen* screen;

  static void window_resize_callback(GLFWwindow* window, int width, int height);
};
}
}


