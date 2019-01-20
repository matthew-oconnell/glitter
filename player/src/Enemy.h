#pragma once
#include "Player.h"

namespace Glitter {
namespace Player {
class Enemy : public Player {
 public:
  Enemy(Screen* s);
  void update();
  void setTarget(Player* p);
  void die();
  bool isAlive() const;
 private:
  int health = 1;
  Screen* screen;
  float speed = 0.04f;
  Player* target;
  void clampToScreen();
};
}
}
