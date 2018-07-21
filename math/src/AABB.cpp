#include <algorithm>
#include "AABB.h"
using namespace Glitter;
using namespace Math;

bool AABB::intersect(const AABB::Box2d &a, const AABB::Box2d &b) {
  auto [a_lo, a_hi] = a;
  auto [b_lo, b_hi] = b;
  if(a_lo.x > b_hi.x)
    return false;
  if(a_lo.y > b_hi.y)
    return false;
  if(a_hi.x < b_lo.x)
    return false;
  if(a_hi.y < b_lo.y)
    return false;
  return true;
}
Vec2d AABB::clamp(const Glitter::Math::AABB::Box2d &box, Glitter::Math::Vec2d c) {
  auto [lo, hi] = box;
  c.x = std::clamp(c.x, lo.x, hi.x);
  c.y = std::clamp(c.y, lo.y, hi.y);
  return c;
}
