#include <catch.hpp>
#include <Camera.h>
using namespace Glitter;

TEST_CASE("Camera Exists"){
  Camera s;
  s.setPixelsPerMeter(20.0f);
  s.windowResize(200, 200);
  REQUIRE(s.onScreen({0.5f, 0.5f}, {0.6f, 0.6f}));
  REQUIRE(!s.onScreen({-0.6f, -0.6f}, {-0.5f, -0.5f}));
}

TEST_CASE("Camera can convert from world to screen location"){
  Camera s;
  s.setPixelsPerMeter(10.0f);
  s.windowResize(200, 200);
  auto screen_location = s.convertWorldToRender({0.0f, 0.0f});
  REQUIRE(screen_location.x == -1.0);
  REQUIRE(screen_location.y == -1.0);

 screen_location = s.convertWorldToRender({20.0f, 20.0f});
  REQUIRE(screen_location.x == 1.0);
  REQUIRE(screen_location.y == 1.0);

  screen_location = s.convertWorldToRender({10.0f, 10.0f});
  REQUIRE(screen_location.x == 0.0);
  REQUIRE(screen_location.y == 0.0);
}

TEST_CASE("Camera can convert from screen to world"){
  Camera s;
  s.setPixelsPerMeter(10.0f);
  s.windowResize(200, 200);
  auto world_location = s.convertScreenToWorld({0,0});
  REQUIRE(world_location.x == 0.0);
  REQUIRE(world_location.y == 0.0);

  world_location = s.convertScreenToWorld({200,100});
  REQUIRE(world_location.x == 20.0);
  REQUIRE(world_location.y == 10.0);

}
