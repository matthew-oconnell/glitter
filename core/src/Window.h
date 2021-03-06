#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Camera.h>
namespace Glitter {
class Window {
 public:
  Window(Camera * screen, std::string title);
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
  Camera* screen;

  static void window_resize_callback(GLFWwindow* window, int width, int height);
};
}


