#pragma once

#include <Vector2d.h>
#include "Input.h"

namespace Glitter {
  namespace Player {
    class First {
    public:
        explicit First(Input* input);
        Glitter::Math::Vec2d acceleration();
        float mass();
    private:
        Input* input;
    };
  }
}

