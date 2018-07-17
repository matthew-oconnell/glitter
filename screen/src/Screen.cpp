#include <Vector2d.h>
#include "Screen.h"

using namespace Glitter;
void Screen::setWorldLocationRange(Math::Vec2d lo, Math::Vec2d hi) {
  world_location_lo = lo;
  world_location_hi = hi;
}
bool Screen::onScreen(Math::Vec2d lo, Math::Vec2d hi) {
  if(lo.x > world_location_hi.x || lo.y > world_location_hi.y || hi.x < world_location_lo.x || hi.y < world_location_lo.y)
    return false;
  return true;
}
