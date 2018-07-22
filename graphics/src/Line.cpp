#include <algorithm>
#include <gl/GLEW.h>
#include "Line.h"
using namespace Glitter;
using namespace Graphics;

Line::Line(Math::Vec2d b, Math::Vec2d e) :begin(b), end(e) {

}
std::tuple<Math::Vec2d, Math::Vec2d> Line::getBounds() const {
  auto lo = begin;
  lo.x = std::min(lo.x, end.x);
  lo.y = std::min(lo.y, end.x);
  auto hi = begin;
  hi.x = std::max(hi.x, end.x);
  hi.y = std::max(hi.y, end.x);
  return {lo, hi};
}
void Line::render(Math::Vec2d world_location, Screen *s) {
  auto world_begin = begin + world_location;
  auto world_end = end + world_location;
  glBegin(GL_LINE_STRIP);
  auto render_begin = s->convertWorldToRender(world_begin);
  auto render_end = s->convertWorldToRender(world_end);
  glColor4f(1.0f,0.0f,0.0f,1.0f);
  glVertex2d(render_begin.x, render_begin.y);
  glVertex2d(render_end.x, render_end.y);
  glEnd();
}
