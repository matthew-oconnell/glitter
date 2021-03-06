#include <iostream>
#include <Game.h>

void initialize();
void finalize();
void thankThirdParty();

int main() {
  thankThirdParty();
  initialize();
  Glitter::Core::Game engine("Glitter");
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
               "\n"
               "OpenGL Mathematics: https://glm.g-truc.net"
               "\n"
               "SoLoud: http://sol.gfxile.net/soloud/"
               "\n"
               "FreeType: https://www.freetype.org/"
               "\n"
               "\n"
               "A big thank you to all the artists that have made their assets available:"
               "Sound Effects: www.kenney.nl"
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
