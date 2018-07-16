#pragma once

#include <Vector2d.h>

namespace Glitter {
  namespace Player {
    class Player {
    public:
        virtual Math::Vec2d acceleration() const = 0;
        virtual float mass() const = 0;
    };
  }
}