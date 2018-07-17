#pragma once

#include <Vector2d.h>
namespace Glitter {
class Screen {
 public:
  void setWorldLocationRange(Math::Vec2d lo, Math::Vec2d hi);
  bool onScreen(Math::Vec2d lo, Math::Vec2d hi);
 private:
  Math::Vec2d world_location_lo;
  Math::Vec2d world_location_hi;
};
}
