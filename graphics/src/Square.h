#pragma once
#include <array>
#include <GL/glew.h>
#include "Model.h"
namespace Glitter {
  namespace Graphics {
    class Square : public Model {
    public:
        inline Square(float width, float height, std::array<GLfloat, 4> color = {1.0f, 1.0f, 1.0f, 1.0f})
                : half_width(0.5f*width), half_height(0.5f*height), color(color){
        }

        void render(Math::Vec2d location) override {

            glBegin(GL_QUADS);
            glColor4f(color[0], color[1], color[2], color[3]);
            glVertex2f( -half_width+location.x,  -half_width+location.y);
            glVertex2f(  half_width+location.x,  -half_width+location.y);
            glVertex2f(  half_width+location.x,   half_width+location.y);
            glVertex2f( -half_width+location.x,   half_width+location.y);
            glEnd();
        }
        std::tuple<Math::Vec2d, Math::Vec2d> getBounds() const override {
          return {Math::Vec2d{-half_width, -half_height}, Math::Vec2d{half_width, half_height}};
        };
    private:
        float half_width, half_height;
        std::array<GLfloat, 4> color;
    };
  }
}