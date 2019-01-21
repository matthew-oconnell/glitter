#pragma once
#include "Window.h"

namespace Glitter {
class Engine {
 public:
  Engine();
  Core::Window* getWindow();
  Screen* getScreen();
 private:
  Screen screen;
  Core::Window window;
};
}


