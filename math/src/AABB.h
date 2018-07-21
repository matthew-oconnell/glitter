#pragma once
#include <tuple>
#include <Vector2d.h>

namespace Glitter {
namespace Math {
namespace AABB {
typedef std::tuple<Vec2d, Vec2d> Box2d;
bool intersect(const Box2d& a, const Box2d& b);
Math::Vec2d clamp(const Box2d& box, Math::Vec2d c);
}
}
}
