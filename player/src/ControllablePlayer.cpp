#include "ControllablePlayer.h"
using namespace Glitter;
using namespace Player;

ControllablePlayer::ControllablePlayer(Glitter::Player::Input* input)
        :input(input){
}
void ControllablePlayer::update() {
    float speed = 0.02f;
    Math::Vec2d a{0,0};
    if(input->pressed(Glitter::Player::Input::KEYS::W))
        a += Math::Vec2d{0.0, speed};
    if(input->pressed(Glitter::Player::Input::KEYS::A))
        a += Math::Vec2d{-speed, 0.0f};
    if(input->pressed(Glitter::Player::Input::KEYS::D))
        a += Math::Vec2d{speed, 0.0f};
    if(input->pressed(Glitter::Player::Input::KEYS::S))
        a += Math::Vec2d{0.0f, -speed};

    world_location += a;
}
