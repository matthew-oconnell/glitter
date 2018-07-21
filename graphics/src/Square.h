#pragma once
#include <array>
#include <GL/glew.h>
#include <Screen.h>
#include "Model.h"
namespace Glitter {
  namespace Graphics {
    class Square : public Model {
    public:
        Square(float width, float height, std::array<GLfloat, 4> color = {1.0f, 1.0f, 1.0f, 1.0f});

        void render(Math::Vec2d world_location, Screen* s) override;
        std::tuple<Math::Vec2d, Math::Vec2d> getBounds() const override;;
    private:
        float half_width, half_height;
        std::array<GLfloat, 4> color;
    };
  }
}