
#include "Bullet.h"
#include <utility>

using namespace Glitter;
using namespace Player;

void Bullet::render(Camera* s) {
  model->render(world_location, s);
}
void Bullet::update() {
  world_location += direction*speed;
}
Math::AABB::Box2d Bullet::getBoundsWorld() const {
  auto [lo, hi] = model->getWorldBounds();
  return {lo + world_location, hi + world_location};
}
void Bullet::setModel(std::shared_ptr<Graphics::Model> m) {
  model = std::move(m);
}
Bullet::Bullet(Math::Vec2d world_coords, Math::Vec2d d, float s, int dmg)
: world_location(world_coords), direction(d), speed(s), damage_amount(dmg){

}
void Bullet::explode() {
  alive = false;
}
bool Bullet::isAlive() const {
  return alive;
}
int Bullet::damage() {
  return damage_amount;
}
