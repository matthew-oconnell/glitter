#include <utility>

#pragma once
#include <memory>
#include <functional>
#include <Texture.h>
#include <chrono>
#include "Bullet.h"


namespace Glitter {
namespace Player {
class Weapon {
 public:
  inline Weapon(Utilities::ResourceManager& rm) : resource_manager(rm),
                                                  fire_bullets_here(nullptr){
  }
  virtual void shoot(const Math::Vec2d& world_location) = 0;
  inline void putBulletsHere(std::function<void(std::shared_ptr<Bullet>)> here) {
    fire_bullets_here = std::move(here);
  }
 protected:
  Utilities::ResourceManager& resource_manager;
  std::function<void(std::shared_ptr<Bullet>)> fire_bullets_here;
};

class SingleShooter : public Weapon {
 public:
  inline SingleShooter(Utilities::ResourceManager& rm): Weapon(rm) {
    damage = 1;
    time_last_shot = std::chrono::system_clock::from_time_t(0);
  }

  inline virtual void shoot(const Math::Vec2d& world_location) override {
    if(fire_bullets_here == nullptr){
      printf("Don't know where to shoot bullets\n");
    }
    auto now = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - time_last_shot).count();
    if(elapsed > cooldown_in_ms){
      Math::Vec2d direction = {1.0f, 0.0f};
      auto bullet = std::make_shared<Bullet>(world_location, direction, bullet_speed, damage);
      auto model = std::make_shared<Graphics::Texture>(resource_manager, "assets/bullet.png", 0.1f, 0.1f);
      bullet->setModel(model);
      fire_bullets_here(bullet);
      time_last_shot = now;
    }
  }

  inline virtual void setBulletSpeed(float speed){
    bullet_speed = speed;
  }

  inline virtual void setDamage(int d){
    damage = d;
  }
 private:
  int damage;
  float bullet_speed = 0.3f;
  unsigned int cooldown_in_ms = 300;
  std::chrono::time_point<std::chrono::system_clock> time_last_shot;
};
}
}
