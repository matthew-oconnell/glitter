#include <catch.hpp>
#include <Vector2d.h>

using namespace Glitter;
using namespace Math;

TEST_CASE("Vector2d exists") {
    Vec2d v{50.0f, 12.0f};
    REQUIRE(v.x == 50.0f);
    REQUIRE(v.y == 12.0f);
}

TEST_CASE("Vector2d scale"){
    Vec2d v{50.0f, 12.0f};
    v *= 2.0f;
    REQUIRE(v.x == 100.0f);
    REQUIRE(v.y ==  24.0f);
}

TEST_CASE("Vector2d divide"){
    Vec2d v{50.0f, 12.0f};
    v /= 2.0f;
    REQUIRE(v.x == 25.0f);
    REQUIRE(v.y ==  6.0f);
}

TEST_CASE("Vector2d addition"){
    Vec2d a{50.0f, 12.0f};
    Vec2d b{50.0f, 12.0f};
    auto v = a+b;
    REQUIRE(v.x == 100.0f);
    REQUIRE(v.y ==  24.0f);
}

TEST_CASE("Vector2d subtraction"){
    Vec2d a{50.0f, 12.0f};
    Vec2d b{50.0f, 6.0f};
    auto v = a-b;
    REQUIRE(v.x == 0.0f);
    REQUIRE(v.y == 6.0f);
}
