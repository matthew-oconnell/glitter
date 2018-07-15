#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <GLFW/glfw3.h>

int main( int argc, char* argv[] ) {
  if(!glfwInit())
    throw std::logic_error("Could not initialize glfw");
  int result = Catch::Session().run( argc, argv );
  glfwTerminate();
  return result;
}
