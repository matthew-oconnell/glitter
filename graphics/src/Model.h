#pragma once
#include <tuple>
#include <Vector2d.h>
namespace Glitter {
  namespace Graphics {
    class Model {
    public:
        virtual void render(Math::Vec2d location) = 0;
        virtual std::tuple<Math::Vec2d, Math::Vec2d> getBounds() const = 0;
    };
  }
}