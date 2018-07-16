#include <catch.hpp>
#include <First.h>
#include "MockInput.h"
#include <Vector2d.h>

using namespace Glitter;
using namespace Player;
using namespace Math;

TEST_CASE("First Exists"){
    MockInput input;
    First player(&input);
}

TEST_CASE("Player move"){
    MockInput input;
    First player(&input);

    input.press(Glitter::Player::Input::W);

    Vec2d a = player.acceleration();
    REQUIRE(a.x == 0.0f);
    REQUIRE(a.y == 1.0f);
}

TEST_CASE("Players have mass"){
    MockInput input;
    First player(&input);

    float f = player.mass();
    REQUIRE(f == 1.0f);
}
