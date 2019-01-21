#include "Engine.h"
using namespace Glitter;

Engine::Engine():
    camera(),
    window(&camera, "Glitter"),
    glew_context(),
    input(window.getGLFWHandle()){

  glfwSetWindowUserPointer(getWindow()->getGLFWHandle(), (void*)this);
}

Window* Engine::getWindow() {
  return &window;
}
Camera* Engine::getCamera() {
  return &camera;
}
GLFWInput* Engine::getInput() {
  return &input;
}
