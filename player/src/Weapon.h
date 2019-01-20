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
  inline Weapon(Utilities::ResourceManager& rm) : resource_manager(rm){
    time_last_shot = std::chrono::system_clock::from_time_t(0);
  }
  void shoot(const Math::Vec2d& world_location) {
    auto now = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - time_last_shot).count();
    if(elapsed > cooldown_in_ms){
      {
        Math::Vec2d direction = {1.0f, 0.0f};
        auto bullet = std::make_shared<Bullet>(world_location, direction, bullet_speed);
        bullet->setModel(std::make_shared<Graphics::Texture>(resource_manager, "assets/bullet.png", 0.1f, 0.1f));
        shoot_bullets_here(bullet);
      }
      {
        Math::Vec2d direction = {1.0f, 0.2f};
        direction = direction.normal();
        auto bullet = std::make_shared<Bullet>(world_location, direction, bullet_speed);
        bullet->setModel(std::make_shared<Graphics::Texture>(resource_manager, "assets/bullet.png", 0.1f, 0.1f));
        shoot_bullets_here(bullet);
      }

      {
        Math::Vec2d direction = {1.0f, -0.2f};
        direction = direction.normal();
        auto bullet = std::make_shared<Bullet>(world_location, direction, bullet_speed);
        bullet->setModel(std::make_shared<Graphics::Texture>(resource_manager, "assets/bullet.png", 0.1f, 0.1f));
        shoot_bullets_here(bullet);
      }
      time_last_shot = now;
    }

  }
  inline void putBulletsHere(std::function<void(std::shared_ptr<Bullet>)> here) {
    shoot_bullets_here = std::move(here);
  }
 protected:
  float bullet_speed = 0.4f;
  unsigned int cooldown_in_ms = 200;
  Utilities::ResourceManager& resource_manager;
  std::function<void(std::shared_ptr<Bullet>)> shoot_bullets_here;
  std::chrono::time_point<std::chrono::system_clock> time_last_shot;

};
}
}
