#include <catch.hpp>
#include <iostream>
#include <GLFW/glfw3.h>
#include <Window.h>


using namespace Glitter;
using namespace Graphics;
TEST_CASE("Window Exists"){
  Window w("test", 800, 600);
  w.update();
  w.closed();
}
