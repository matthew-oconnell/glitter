#include <Vector2d.h>
#include "Screen.h"

using namespace Glitter;
bool Screen::onScreen(Math::Vec2d lo, Math::Vec2d hi) {
  if(lo.x > world_location_hi.x || lo.y > world_location_hi.y || hi.x < world_location_lo.x || hi.y < world_location_lo.y)
    return false;
  return true;
}
Math::Vec2d Screen::convertToScreenCoords(const Math::Vec2d &world_coords) {
  float x_percent = (world_coords.x - world_location_lo.x) / (world_location_hi.x - world_location_lo.x);
  float y_percent = (world_coords.y - world_location_lo.x) / (world_location_hi.y - world_location_lo.y);
  float screen_x = 2.0f*x_percent - 1.0f;
  float screen_y = 2.0f*y_percent - 1.0f;
  return Math::Vec2d{screen_x, screen_y};
}
void Screen::setScreenScale(float s) {
  pixels_per_meter = s;
}
void Screen::windowResize(int width, int height) {
  world_location_lo = {0.0, 0.0};
  world_location_hi = {width/pixels_per_meter, height/pixels_per_meter};
}
