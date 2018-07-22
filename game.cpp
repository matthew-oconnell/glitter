#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Engine.h>
#include <GLFWInput.h>
#include <Idiot.h>
#include <Square.h>
#include <Ally.h>

void initialize();
void finalize();

int main() {
  initialize();

  Glitter::Core::Engine engine("Glitter");
//  auto idiot = std::make_shared<Glitter::Player::Idiot>();
//  idiot->setModel(std::make_shared<Glitter::Graphics::Square>(0.5f, 0.5f));
//  idiot->setWorldLocation({0.0f, 0.0f});
//  engine.addAlly(idiot);


  engine.loop();

  finalize();
  return 0;
}

void initialize() {
  std::cout << "Initializing Glitter" << std::endl;
  if( !glfwInit())
    throw std::logic_error("Could not initialize GLFW!");
  std::cout << "glfw initialized" << std::endl;
}
void finalize() {
  glfwTerminate();
}
