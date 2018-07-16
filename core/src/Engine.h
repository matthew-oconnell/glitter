#pragma once
#include <memory>
#include <string>
#include <array>
struct GLFWwindow;

namespace Glitter {
namespace Core {

class Input;

class Engine {
 public:
  Engine(std::string title, int width, int height);
  void loop();
  void update();
  bool closed();
  Input* getInput();
  int getWidth() const;
  int getHeight() const;
  ~Engine();
  void clear();
 private:
  std::string name;
  GLFWwindow *window_handle;
  int width, height;
  std::shared_ptr<Input> input;
  static void window_resize_callback(GLFWwindow* window, int width, int height);

};
}
}


