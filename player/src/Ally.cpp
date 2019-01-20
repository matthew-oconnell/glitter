#include <Texture.h>
#include "Ally.h"
using namespace Glitter;
using namespace Player;

Ally::Ally(Utilities::ResourceManager& rm, Input* input, Screen* screen_in, std::function<void(std::shared_ptr<Bullet>)> s)
        :resource_manager(rm), input(input), screen(screen_in), shoot_bullets_here(s){
}
void Ally::update() {
  screen->rangeInWorldCoordinates();
  float speed = 0.2f;
  move(speed);
  setWorldLocation(Math::AABB::clamp(screen->rangeInWorldCoordinates(), world_location));
  shoot();
}
void Ally::move(float speed) {
  Math::Vec2d a{0, 0};
  if(input->pressed(Input::W))
        a += Math::Vec2d{0.0, speed};
  if(input->pressed(Input::A))
        a += Math::Vec2d{-speed, 0.0f};
  if(input->pressed(Input::D))
        a += Math::Vec2d{speed, 0.0f};
  if(input->pressed(Input::S))
        a += Math::Vec2d{0.0f, -speed};

  setWorldLocation(world_location+a);
}
void Ally::render(Screen *s) {
    Player::render(s);
    last_screen_range = s->rangeInWorldCoordinates();
}
void Ally::shoot() {
  if(! input->pressed(Input::SPACE)) return;

  auto cursor_location = screen->convertScreenToWorld(input->getCursorLocation());
  auto direction = cursor_location - world_location;
  direction = direction.normal();
  float bullet_speed = 0.4f;
  auto bullet = std::make_shared<Bullet>(world_location, direction, bullet_speed);
  bullet->setModel(std::make_shared<Graphics::Texture>(resource_manager, "assets/bullet.png", 0.1f, 0.1f));
  shoot_bullets_here(bullet);
}
