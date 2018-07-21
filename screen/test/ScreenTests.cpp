#include <catch.hpp>
#include <Screen.h>
using namespace Glitter;

TEST_CASE("Screen Exists"){
  Screen s;
  s.windowResize({0.0f, 0.0f}, {100.0f, 100.0f});
  REQUIRE(s.onScreen({0.5f, 0.5f}, {0.6f, 0.6f}));
  REQUIRE(!s.onScreen({-0.6f, -0.6f}, {-0.5f, -0.5f}));
}

TEST_CASE("Screen can convert from world to screen location"){
  Screen s;
  s.windowResize({0.0f, 0.0f}, {100.0f, 100.0f});
  auto screen_location = s.convertToScreenCoords({0.0f, 0.0f});
  REQUIRE(screen_location.x == -1.0);
  REQUIRE(screen_location.y == -1.0);

 screen_location = s.convertToScreenCoords({100.0f, 100.0f});
  REQUIRE(screen_location.x == 1.0);
  REQUIRE(screen_location.y == 1.0);

  screen_location = s.convertToScreenCoords({50.0f, 50.0f});
  REQUIRE(screen_location.x == 0.0);
  REQUIRE(screen_location.y == 0.0);
}
