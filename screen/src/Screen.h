#pragma once

#include <Vector2d.h>
#include <AABB.h>
namespace Glitter {
class Screen {
 public:
  void setPixelsPerMeter(float scale);
  void windowResize(int width, int height);
  Math::Vec2d convertWorldToRender(const Math::Vec2d &world_coords);
  Math::Vec2d convertScreenToWorld(const Math::Vec2d &screen_coords);
  bool onScreen(Math::Vec2d lo, Math::Vec2d hi);
  Math::AABB::Box2d rangeInWorldCoordinates() const;
 private:
  float pixels_per_meter = 1.0;
  int width;
  int height;
  Math::Vec2d world_location_lo;
  Math::Vec2d world_location_hi;
};
}
