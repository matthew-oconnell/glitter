#include <catch.hpp>
#include <Vec3d.h>
using namespace Glitter;
using namespace Math;

TEST_CASE("Vector3d exists"){
    Vec3d v{1.0f, 0.0f, 0.0f};
}
TEST_CASE("Vector3d scale") {
    Vec3d v{1.0f, 0.1f, 0.2f};

    v *= 2.0;
    REQUIRE(v.x == 2.0f);
    REQUIRE(v.y == 0.2f);
    REQUIRE(v.z == 0.4f);
}

TEST_CASE("Vector3d division") {
    Vec3d v{1.0f, 0.1f, 0.2f};

    v /= 2.0;
    REQUIRE(v.x == 0.5f);
    REQUIRE(v.y == 0.05f);
    REQUIRE(v.z == 0.1f);
}

TEST_CASE("Vector3d addition") {
    Vec3d a{1.0f, 0.1f, 0.2f};
    Vec3d b{1.0f, 0.1f, 0.2f};

    auto v = a+b;
    REQUIRE(v.x == 2.0f);
    REQUIRE(v.y == 0.20f);
    REQUIRE(v.z == 0.4f);
}

TEST_CASE("Vector3d subtraction") {
    Vec3d a{1.0f, 0.1f, 0.2f};
    Vec3d b{0.5f, 0.1f, 0.2f};

    auto v = a-b;
    REQUIRE(v.x == 0.5f);
    REQUIRE(v.y == 0.0f);
    REQUIRE(v.z == 0.0f);
}

TEST_CASE("Can output vec3d"){
    Vec3d a{1.0f, 0.1f, 0.2f};
    std::cout << a << std::endl;
}
