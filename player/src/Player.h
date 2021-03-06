#pragma once

#include <Vector2d.h>
#include <Model.h>
#include <utility>
namespace Glitter {
namespace Player {
class Player {
 public:
  virtual void update() = 0;

  void setModel(std::shared_ptr<Graphics::Model> m);
  virtual void render(Camera* s);
  void setWorldLocation(Math::Vec2d location);
  Math::Vec2d getWorldLocation() const;
  std::tuple<Math::Vec2d, Math::Vec2d> getBoundsWorld() const;
 protected:
  Math::Vec2d world_location;
  std::shared_ptr<Graphics::Model> model = nullptr;
  friend class Player;
};

inline void Player::setWorldLocation(Math::Vec2d loc) {
  world_location = loc;
}
inline Math::Vec2d Player::getWorldLocation() const {
  return world_location;
}
inline void Player::setModel(std::shared_ptr<Graphics::Model> m) {
  model = std::move(m);
}
inline void Player::render(Camera* screen){
  if(model != nullptr)
    model->render(world_location, screen);
}
inline std::tuple<Math::Vec2d, Math::Vec2d> Player::getBoundsWorld() const {
  auto [lo, hi] = model->getWorldBounds();
  lo += world_location;
  hi += world_location;
  return {lo, hi};
}
}
}