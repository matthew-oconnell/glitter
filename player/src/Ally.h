#pragma once

#include <Vector2d.h>
#include <AABB.h>
#include <functional>
#include <ModelDatabase.h>
#include "Input.h"
#include "Player.h"
#include "Bullet.h"
#include "Weapon.h"

namespace Glitter {
namespace Player {
class Ally :public Player {
 public:
  Ally(Engine* engine, std::function<void(std::shared_ptr<Bullet>)> shoot_bullets_here);
  void update() override;
  void render(Camera* s) override;
  void equipWeapon(std::shared_ptr<Weapon> w);
 private:
  Input* input;
  Camera* camera;
  std::shared_ptr<Weapon> weapon;
  void move(float speed);
  void shoot();
};
}
}

