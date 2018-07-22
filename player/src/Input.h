#pragma once
#include <Vector2d.h>

namespace Glitter {
  namespace Player {
    class Input {
    public:
        enum KEYS {
            W, A, S, D, SPACE
        };
        virtual bool pressed(KEYS k) const = 0;
        virtual Math::Vec2d getCursorLocation() const = 0;
    };
  }
}