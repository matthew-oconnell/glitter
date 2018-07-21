#pragma once

#include <Vector2d.h>
namespace Glitter {
class Screen {
 public:
  void setScreenScale(float scale);
  void windowResize(int width, int height);
  Math::Vec2d convertToScreenCoords(const Math::Vec2d& world_coords);
  bool onScreen(Math::Vec2d lo, Math::Vec2d hi);
 private:
  float pixels_per_meter = 1.0;
  Math::Vec2d world_location_lo;
  Math::Vec2d world_location_hi;
};
}
