#pragma once
#include "Window.h"
#include "Camera.h"
#include "GlewContext.h"
#include "GLFWInput.h"

namespace Glitter {
class Engine {
 public:
  Engine();
  Window* getWindow();
  Camera* getCamera();
  GLFWInput* getInput();
 private:
  Camera camera;
  Window window;
  GlewContext glew_context;
  GLFWInput input;
};
}


