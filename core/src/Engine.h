#pragma once
#include <memory>
#include <string>
#include <array>
#include "GlewContext.h"
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
  int width, height;
  GLFWwindow *window_handle;
  std::shared_ptr<Input> input;
  GlewContext glew_context;
  static void window_resize_callback(GLFWwindow* window, int width, int height);


  GLFWwindow* createWindow(std::string title, int width, int height);

};
}
}


