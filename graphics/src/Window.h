#pragma once
#include <string>
#include <array>
struct GLFWwindow;

    namespace Glitter {
namespace Graphics {
class Window {

 public:
  Window(std::string title, int width, int height);
  void update();
  bool closed();
  ~Window();
  void clear();
 private:
  std::string name;
  GLFWwindow *window_handle;
};
}
}


