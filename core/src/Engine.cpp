#include "Engine.h"
using namespace Glitter;


Engine::Engine():
    camera(),
    window(&camera, "Glitter") {
}

Window* Engine::getWindow() {
  return &window;
}
Camera* Engine::getCamera() {
  return &camera;
}
