#pragma once

#include <Vector2d.h>
namespace Glitter {
  namespace Graphics {
    class Model {
    public:
        virtual void render(Math::Vec2d location) = 0;
    };
  }
}