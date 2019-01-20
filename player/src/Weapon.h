#pragma once
#include <memory>
#include <functional>
#include <Texture.h>
#include "Bullet.h"


namespace Glitter {
namespace Player {
class Weapon {
 public:
  inline Weapon(Utilities::ResourceManager& rm) : resource_manager(rm){}
  void shoot(const Math::Vec2d& world_location) {
    float bullet_speed = 0.4f;
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

  }
  inline void putBulletsHere(std::function<void(std::shared_ptr<Bullet>)> here) {
    shoot_bullets_here = here;
  }
 protected:
  Utilities::ResourceManager& resource_manager;
  std::function<void(std::shared_ptr<Bullet>)> shoot_bullets_here;
};
}
}
