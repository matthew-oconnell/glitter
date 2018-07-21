#pragma once
#include <Vector2d.h>

namespace Glitter {
namespace Math {
namespace AABB {
typedef std::tuple<Vec2d, Vec2d> Box2d;
  inline bool intersect(const Box2d& a, const Box2d& b){
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
}
}
}
