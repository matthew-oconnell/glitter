#pragma once

#include <Vector2d.h>
#include "Input.h"
#include "Player.h"

namespace Glitter {
  namespace Player {
    class ControllablePlayer :public Player {
    public:
        explicit ControllablePlayer(Input* input);
        Glitter::Math::Vec2d acceleration() const;
        float mass() const;
    private:
        Input* input;
    };
  }
}

