#include "MockInput.h"

bool MockInput::pressed(Glitter::Player::Input::KEYS key) const {
    return keyboard_keys[key];
}
MockInput::MockInput() {
    for(auto& k : keyboard_keys)
        k = false;
    for(auto& b : mouse_buttons)
        b = false;
}
void MockInput::press(Glitter::Player::Input::KEYS key) {
    keyboard_keys[key] = true;
}
void MockInput::release(Glitter::Player::Input::KEYS key) {
    keyboard_keys[key] = false;
}
