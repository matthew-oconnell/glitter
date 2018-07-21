#include <catch.hpp>
#include <Vector2d.h>
#include <iostream>

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
TEST_CASE("Vector2d summation"){
    Vec2d a{50.0f, 12.0f};
    Vec2d b{50.0f, 12.0f};
    a+=b;
    REQUIRE(a.x == 100.0f);
    REQUIRE(a.y ==  24.0f);
}

TEST_CASE("Vector2d subtraction"){
    Vec2d a{50.0f, 12.0f};
    Vec2d b{50.0f, 6.0f};
    auto v = a-b;
    REQUIRE(v.x == 0.0f);
    REQUIRE(v.y == 6.0f);
}

TEST_CASE("Vector2d multiply by scalar"){
    Vec2d a{50.0f, 12.0f};
    auto v = a*0.5f;
    REQUIRE(v.x == 25.0f);
    REQUIRE(v.y ==  6.0f);

}


TEST_CASE("Can output vec"){
    Vec2d a{1.0f, 0.1f};
    std::cout << a << std::endl;
}
