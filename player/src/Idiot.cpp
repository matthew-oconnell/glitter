#include "Idiot.h"
Glitter::Math::Vec2d Glitter::Player::Idiot::acceleration() const {
    return Math::Vec2d{0.0f, 0.0f};
}
float Glitter::Player::Idiot::mass() const {
    return 10.0f;
}
