#pragma once

#include <AABB.h>
#include <Model.h>
namespace Glitter {
namespace Player {
class Bullet {
 public:
  Bullet(Math::Vec2d world_coords, Math::Vec2d direction, float speed, int damage);
  void setModel(std::shared_ptr<Graphics::Model> m);
  void render(Camera* s);
  void update();
  bool isAlive() const;
  void explode();
  int damage();
  Math::AABB::Box2d getBoundsWorld() const;
 private:
  bool alive = true;
  Math::Vec2d world_location;
  std::shared_ptr<Graphics::Model> model;
  Math::Vec2d direction;
  float speed;
  int damage_amount;
};
}
}
