#pragma once
#include "Window.h"

namespace Glitter {
class Engine {
 public:
  Engine();
  Core::Window* getWindow();
  Camera* getCamera();
 private:
  Camera screen;
  Core::Window window;
};
}


