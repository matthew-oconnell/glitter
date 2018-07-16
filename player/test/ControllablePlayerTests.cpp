#include <catch.hpp>
#include <ControllablePlayer.h>
#include "MockInput.h"
#include <Vector2d.h>

using namespace Glitter;
using namespace Player;
using namespace Math;

TEST_CASE("ControllablePlayer Exists"){
    MockInput input;
    ControllablePlayer player(&input);
}

TEST_CASE("Player move"){
    MockInput input;
    ControllablePlayer player(&input);

    input.press(Glitter::Player::Input::W);

    Vec2d a = player.acceleration();
    REQUIRE(a.x == 0.0f);
    REQUIRE(a.y == 1.0f);
}

TEST_CASE("Players have mass"){
    MockInput input;
    ControllablePlayer player(&input);

    float f = player.mass();
    REQUIRE(f == 1.0f);
}
