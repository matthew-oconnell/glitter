#pragma once

#include <Vector2d.h>
#include <AABB.h>
#include "Input.h"
#include "Player.h"

namespace Glitter {
  namespace Player {
    class ControllablePlayer :public Player {
    public:
        explicit ControllablePlayer(Input* input);
        void update();
        void render(Screen* s) override;
    private:
        Input* input;
        Math::AABB::Box2d last_screen_range;
    };
  }
}

