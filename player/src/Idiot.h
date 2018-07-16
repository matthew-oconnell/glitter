#pragma once
#include "Player.h"

namespace Glitter {
  namespace Player {
    class Idiot : public Player {
    public:
        Math::Vec2d acceleration() const override;
        float mass() const override;
    };
  }
}