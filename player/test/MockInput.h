#pragma once
#include <array>
#include <Input.h>

class MockInput : public Glitter::Player::Input {
public:
    MockInput();
    void press(Glitter::Player::Input::KEYS key);
    void release(Glitter::Player::Input::KEYS key);
    bool pressed(Glitter::Player::Input::KEYS key) const override;
private:
    const static int MAX_KEYBOARD_KEYS = 1024;
    const static int MAX_MOUSE_BUTTONS = 32;
    std::array<bool, MAX_KEYBOARD_KEYS> keyboard_keys;
    std::array<bool, MAX_MOUSE_BUTTONS> mouse_buttons;
};