#include <tuple>
#include <Vector2d.h>
#include <AABB.h>
#include "Screen.h"

using namespace Glitter;
bool Screen::onScreen(Math::Vec2d lo, Math::Vec2d hi) const {
  return (Math::AABB::intersect({lo, hi}, {world_location_lo, world_location_hi}));
}
Math::Vec2d Screen::convertWorldToRender(const Math::Vec2d &world_coords) {
  float x_percent = (world_coords.x - world_location_lo.x) / (world_location_hi.x - world_location_lo.x);
  float y_percent = (world_coords.y - world_location_lo.x) / (world_location_hi.y - world_location_lo.y);
  float screen_x = 2.0f*x_percent - 1.0f;
  float screen_y = 2.0f*y_percent - 1.0f;
  return Math::Vec2d{screen_x, screen_y};
}
void Screen::setPixelsPerMeter(float s) {
  pixels_per_meter = s;
}
void Screen::windowResize(int w, int h) {
  width = w;
  height = h;
  world_location_lo = {0.0, 0.0};
  world_location_hi = {width/pixels_per_meter, height/pixels_per_meter};
}
Math::AABB::Box2d Screen::rangeInWorldCoordinates() const {
  return {world_location_lo, world_location_hi};
}
Math::Vec2d Screen::convertScreenToWorld(const Math::Vec2d &screen_coords) {
  auto percent = Math::Vec2d{screen_coords.x / float(width), 1.0f - screen_coords.y / float(height)};
  auto world_dx = world_location_hi - world_location_lo;
  auto world = Math::Vec2d{percent.x*world_dx.x, percent.y*world_dx.y};
  return world;
}
