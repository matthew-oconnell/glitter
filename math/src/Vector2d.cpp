
#include "Vector2d.h"
using namespace Glitter;
using namespace Math;

void Vec2d::operator*=(float f) {
  x *= f;
  y *= f;
}
void Vec2d::operator/=(float f) {
  x /= f;
  y /= f;
}
Vec2d Vec2d::operator+(Vec2d rhs) {
  return Vec2d{this->x + rhs.x, this->y + rhs.y};
}
Vec2d Vec2d::operator*(float f) {
  return Vec2d{this->x*f, this->y*f};
}
Vec2d Vec2d::operator-(Vec2d rhs) {
  return Vec2d{this->x - rhs.x, this->y - rhs.y};
}
void Vec2d::operator+=(Vec2d rhs) {
  this->x += rhs.x;
  this->y += rhs.y;
}
float Vec2d::magnitude() const {
  return std::sqrt(this->x*this->x + this->y*this->y);
}
Vec2d Vec2d::normal() const {
  auto out = *this;
  out /= magnitude();
  return out;
}
std::ostream &operator<<(std::ostream &stream, const Vec2d &obj) {
  stream<<obj.x<<" "; stream<<obj.y;
  return stream;
}
