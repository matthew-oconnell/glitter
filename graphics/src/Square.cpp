#include "Square.h"

using namespace Glitter;

Graphics::Square::Square(float width, float height, std::array<GLfloat, 4> color)
    : half_width(0.5f*width), half_height(0.5f*height), color(color){
}
void Graphics::Square::render(Math::Vec2d world_location, Screen* s) {

  glBegin(GL_QUADS);
  glColor4f(color[0], color[1], color[2], color[3]);
  std::array<Math::Vec2d, 4> corners_world = {
      Math::Vec2d{-half_width+world_location.x,  -half_width+world_location.y},
      Math::Vec2d{ half_width+world_location.x,  -half_width+world_location.y},
      Math::Vec2d{ half_width+world_location.x,   half_width+world_location.y},
      Math::Vec2d{-half_width+world_location.x,   half_width+world_location.y}
  };
  for(auto c: corners_world){
    c = s->convertToScreenCoords(c);
    glVertex2d(c.x, c.y);
  }
  glEnd();
}
std::tuple<Math::Vec2d, Math::Vec2d> Glitter::Graphics::Square::getBounds() const {
  return {Math::Vec2d{-half_width, -half_height}, Math::Vec2d{half_width, half_height}};
}
