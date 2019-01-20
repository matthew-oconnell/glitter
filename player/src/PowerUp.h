#pragma once

#include "Ally.h"

namespace Glitter {
namespace Player {
class PowerUp {
 public:
  inline PowerUp(Utilities::ResourceManager& rm, const Math::Vec2d& world_loc) : resource_manager(rm), world_location(world_loc){}
  inline void powerUp(Ally* p, std::function<void(std::shared_ptr<Bullet>)> fire_bullets_here){
    auto w = std::make_shared<SingleShooter>(resource_manager);
    w->setDamage(2);
    w->putBulletsHere(fire_bullets_here);
    p->equipWeapon(w);
  }
  inline void consume() {
    alive = false;
  }
  inline void setModel(std::shared_ptr<Graphics::Model> m){
    model = m;
  }
  inline void render(Screen* s){
    model->render(world_location, s);
  }
  inline std::tuple<Math::Vec2d, Math::Vec2d> getBoundsWorld(){
    auto [lo, hi] = model->getWorldBounds();
    lo += world_location;
    hi += world_location;
    return {lo, hi};
  }
  inline bool isAlive() const {
    return alive;
  }
 protected:
  Utilities::ResourceManager& resource_manager;
  Math::Vec2d world_location;
  std::shared_ptr<Graphics::Model> model;
  bool alive = true;
};
}
}
