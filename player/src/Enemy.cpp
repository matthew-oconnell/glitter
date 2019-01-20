#include <random>
#include "Enemy.h"
using namespace Glitter::Player;

void Enemy::update() {
  if(target != nullptr) {
    auto direction = target->getWorldLocation() - world_location;
    direction = direction.normal();
    world_location += direction*speed;
  }
  clampToScreen();
}
void Enemy::clampToScreen() {
  auto [lo, hi] = this->getBoundsWorld();
  if(!this->screen->onScreen(lo, hi)){
    this->world_location = Glitter::Math::AABB::clamp({lo, hi}, this->world_location);
  }
}
void Enemy::setTarget(Glitter::Player::Player* p) {
  target = p;
}
Enemy::Enemy(Glitter::Screen *s) :screen(s) {
}
void Enemy::die() {
  health = 0;
}
bool Enemy::isAlive() const {
  return health > 0;
}
