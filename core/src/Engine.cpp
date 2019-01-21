#include "Engine.h"
Glitter::Engine::Engine():
    screen(),
    window(&screen, "Glitter") {
}

Glitter::Core::Window *Glitter::Engine::getWindow() {
  return &window;
}
Glitter::Camera *Glitter::Engine::getCamera() {
  return &screen;
}
