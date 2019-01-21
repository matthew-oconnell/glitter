#pragma once
#include "Player.h"

namespace Glitter {
namespace Player {
class Enemy : public Player {
 public:
  Enemy(Camera* s);
  void update();
  void setTarget(Player* p);
  void die();
  void takeDamage(int damage);
  void setHealth(int h);
  bool isAlive() const;
 private:
  int health = 1;
  Camera* screen;
  float speed = 0.04f;
  Player* target;
  void clampToScreen();
};
}
}
