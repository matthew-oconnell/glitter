#pragma once

#include <GL/glew.h>
#include "Model.h"
namespace Glitter {
  namespace Graphics {
    class Square : public Model {
    public:
        inline Square(float width, float height)
                : half_width(0.5f*width), half_height(0.5f*height){
        }

        void render(Math::Vec2d location) override {

            glBegin(GL_QUADS);
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
    };
  }
}