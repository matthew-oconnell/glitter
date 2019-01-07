#pragma once

#include <Vector2d.h>
#include <AABB.h>
#include <functional>
#include "Input.h"
#include "Player.h"
#include "Bullet.h"

namespace Glitter {
namespace Player {
class Ally :public Player {
 public:
  Ally(Input* input, Screen* screen, std::function<void(std::shared_ptr<Bullet>)> shoot_bullets_here);
  void update() override;
  void render(Screen* s) override;
 private:
  Input* input;
  Screen* screen;
  std::function<void(std::shared_ptr<Bullet>)> shoot_bullets_here;
  Math::AABB::Box2d last_screen_range;
  void move(float speed);
  void shoot();
};
}
}

