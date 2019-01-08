#include <iostream>
#include <Engine.h>
#include <Idiot.h>
#include <Square.h>
#include <Ally.h>
#include "Text.h"

void initialize();
void finalize();
void thankThirdParty();

int main() {
  thankThirdParty();
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
void thankThirdParty() {
  std::cout << "\n"
               "Thank you to the following libraries: \n"

               "The OpenGL Extension Wrangler Library\n"
               "Copyright (C) 2002-2007, Milan Ikits <milan ikits[]ieee org>\n"
               "Copyright (C) 2002-2007, Marcelo E. Magallon <mmagallo[]debian org>\n"
               "Copyright (C) 2002, Lev Povalahev\n"
               "All rights reserved.\n"
               "\n"
               "Catch2: https://github.com/catchorg/Catch2\n"
               "\n"
               "GLFW: https://github.com/glfw/glfw"
               << std::endl;
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
