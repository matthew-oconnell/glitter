#include <catch.hpp>
#include <Screen.h>
using namespace Glitter;

TEST_CASE("Screen Exists"){
  Screen s;
  s.setWorldLocationRange({0.0f, 0.0f}, {100.0f, 100.0f});
  REQUIRE(s.onScreen({0.5f, 0.5f}, {0.6f, 0.6f}));
  REQUIRE(!s.onScreen({-0.6f, -0.6f}, {-0.5f, -0.5f}));
}

