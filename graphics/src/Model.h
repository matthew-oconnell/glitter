#pragma once
#include <tuple>
#include <Vector2d.h>
#include <Screen.h>
namespace Glitter {
  namespace Graphics {
    class Model {
    public:
        virtual void render(Math::Vec2d world_location, Screen* s) = 0;
        virtual std::tuple<Math::Vec2d, Math::Vec2d> getWorldBounds() const = 0;
    };
  }
}