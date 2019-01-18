#pragma once

#include <Vector2d.h>
#include <AABB.h>
#include <functional>
#include <ResourceManager.h>
#include "Input.h"
#include "Player.h"
#include "Bullet.h"

namespace Glitter {
namespace Player {
class Ally :public Player {
 public:
  Ally(Utilities::ResourceManager& rm, Input* input, Screen* screen, std::function<void(std::shared_ptr<Bullet>)> shoot_bullets_here);
  void update() override;
  void render(Screen* s) override;
 private:
  Utilities::ResourceManager& resource_manager;
  Input* input;
  Screen* screen;
  std::function<void(std::shared_ptr<Bullet>)> shoot_bullets_here;
  Math::AABB::Box2d last_screen_range;
  void move(float speed);
  void shoot();
};
}
}

