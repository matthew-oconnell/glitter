#pragma once
#include <iostream>

namespace Glitter {
namespace Math {
struct Vec2d {
  float x;
  float y;

  void operator*=(float f);
  void operator/=(float f);
  Vec2d operator+(Vec2d rhs);
  Vec2d operator*(float f);
  Vec2d operator-(Vec2d rhs);
  void operator+=(Vec2d rhs);
  float magnitude() const;
  Vec2d normal() const;
};
std::ostream& operator<<(std::ostream& stream, const Vec2d& obj);
}
}