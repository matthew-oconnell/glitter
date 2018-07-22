#include <catch.hpp>
#include <AABB.h>
using namespace Glitter;
using namespace Math;

TEST_CASE("AABB can determine intersection"){
  AABB::Box2d a = {{0.0f, 0.0f}, {1.0f, 1.0f}};
  AABB::Box2d b = {{2.0f, 2.0f}, {3.0f, 3.0f}};
  REQUIRE_FALSE(AABB::intersect(a, b));

  b = AABB::Box2d{{0.25f, 0.25f}, {0.75f, 0.75f}};
  REQUIRE(AABB::intersect(a, b));
}

TEST_CASE("Clamp to AABB"){
  AABB::Box2d a = {{0.0f, 0.0f}, {1.0f, 1.0f}};
  auto c = AABB::clamp(a, Math::Vec2d{-1.0f, -1.0f});
  REQUIRE(c.x == 0.0f);
  REQUIRE(c.y == 0.0f);
  c = AABB::clamp(a, Math::Vec2d{0.25f, -1.0f});
  REQUIRE(c.x == 0.25f);
  REQUIRE(c.y == 0.0f);
}


