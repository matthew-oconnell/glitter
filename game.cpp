#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Engine.h>
#include <GLFWInput.h>
#include <Idiot.h>
#include <Square.h>
#include <ControllablePlayer.h>

void initialize();
void finalize();

int main() {
  initialize();

  Glitter::Core::Engine engine("Glitter", 1280, 720);
//  auto idiot = std::make_shared<Glitter::Player::Idiot>();
//  idiot->setModel(std::make_shared<Glitter::Graphics::Square>(0.5f, 0.5f));
//  idiot->setWorldLocation({0.0f, 0.0f});
//  engine.addPlayer(idiot);

  auto player_one = std::make_shared<Glitter::Player::ControllablePlayer>(engine.getInput());
  player_one->setModel(std::make_shared<Glitter::Graphics::Square>(1.0f, 1.0f, std::array<GLfloat, 4>{0.8f, 0.3f, 0.3f, 1.0f}));
  player_one->setWorldLocation({5.0f, 5.0f});
  engine.addPlayer(player_one);
  glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

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
