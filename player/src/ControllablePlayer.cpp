#include "ControllablePlayer.h"
using namespace Glitter;
using namespace Player;

ControllablePlayer::ControllablePlayer(Input* input, Screen* s)
        :input(input){
}
void ControllablePlayer::update() {
    float speed = 0.5f;
    Math::Vec2d a{0,0};
    if(input->pressed(Input::KEYS::W))
        a += Math::Vec2d{0.0, speed};
    if(input->pressed(Input::KEYS::A))
        a += Math::Vec2d{-speed, 0.0f};
    if(input->pressed(Input::KEYS::D))
        a += Math::Vec2d{speed, 0.0f};
    if(input->pressed(Input::KEYS::S))
        a += Math::Vec2d{0.0f, -speed};

    world_location += a;
}
void ControllablePlayer::render(Screen *s) {
    Player::render(s);
    last_screen_range = s->rangeInWorldCoordinates();
}
