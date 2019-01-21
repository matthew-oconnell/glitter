#pragma once
#include "Window.h"
#include "Camera.h"

namespace Glitter {
class Engine {
 public:
  Engine();
  Window* getWindow();
  Camera* getCamera();
 private:
  Camera camera;
  Window window;
};
}


