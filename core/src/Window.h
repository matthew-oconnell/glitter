#pragma once
#include <string>
#include <GLFW/glfw3.h>
namespace Glitter {
namespace Core {
class Window {
 public:
  Window(std::string title, int width, int height);
  ~Window();
  GLFWwindow* getGLFWHandle();
  void update();
  bool closed();
  int getHeight();
  int getWidth();
 private:
  std::string title;
  int width;
  int height;
  GLFWwindow *window_handle;

  static void window_resize_callback(GLFWwindow* window, int width, int height);
};
}
}


