#pragma once

#include <GL/glew.h>
#include "Model.h"
namespace Glitter {
  namespace Graphics {
    class Square : public Model {
    public:
        inline Square(float width, float height)
                : half_width(0.5*width), half_height(0.5*height){
        }

        void render(Math::Vec2d location) override {

            glBegin(GL_QUADS);
            glVertex2f( -half_width+location.x,  -half_width+location.y);
            glVertex2f(  half_width+location.x,  -half_width+location.y);
            glVertex2f(  half_width+location.x,   half_width+location.y);
            glVertex2f( -half_width+location.x,   half_width+location.y);
            glEnd();
        }
    private:
        float half_width, half_height;
    };
  }
}