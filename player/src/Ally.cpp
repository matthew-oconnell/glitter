#include <Texture.h>
#include "Ally.h"
#include "Weapon.h"
using namespace Glitter;
using namespace Player;

Ally::Ally(ModelDatabase* rm, Input* input, Camera* screen_in, std::function<void(std::shared_ptr<Bullet>)> s)
        :resource_manager(rm), input(input), screen(screen_in), weapon(std::make_shared<SingleShooter>(rm)) {
  weapon->putBulletsHere(s);
}
void Ally::update() {
  screen->rangeInWorldCoordinates();
  float speed = 0.1f;
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
void Ally::render(Camera *s) {
    Player::render(s);
    last_screen_range = s->rangeInWorldCoordinates();
}
void Ally::shoot() {
  if(! input->pressed(Input::SPACE)) return;
  if(weapon == nullptr)
    printf("Ally has no weapon equipped\n");
  else
    weapon->shoot(world_location);
}
void Ally::equipWeapon(std::shared_ptr<Weapon> w) {
  weapon = std::move(w);
}
