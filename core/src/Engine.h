#pragma once
#include <memory>
#include <string>
#include <array>
#include "GlewContext.h"
#include "Window.h"
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
  Window* getWindow();
  void clear();
 private:
  std::string name;
  std::shared_ptr<Window> window;
  std::shared_ptr<Input> input;
  GlewContext glew_context;
  void drawStupiderCursor();
};
}
}


