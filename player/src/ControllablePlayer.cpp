#include "ControllablePlayer.h"
using namespace Glitter;
using namespace Player;

ControllablePlayer::ControllablePlayer(Glitter::Player::Input* input)
        :input(input){
}
Glitter::Math::Vec2d ControllablePlayer::acceleration() const {
    Math::Vec2d a{0,0};
    if(input->pressed(Glitter::Player::Input::KEYS::W))
        a += Math::Vec2d{0.0f, 1.0f};
    if(input->pressed(Glitter::Player::Input::KEYS::A))
        a += Math::Vec2d{-1.0f, 0.0f};
    if(input->pressed(Glitter::Player::Input::KEYS::D))
        a += Math::Vec2d{1.0f, 0.0f};
    if(input->pressed(Glitter::Player::Input::KEYS::S))
        a += Math::Vec2d{0.0f, -1.0f};
    return a;
}
float ControllablePlayer::mass() const {
    return 1.0;
}
