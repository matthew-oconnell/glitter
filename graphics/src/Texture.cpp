#include <string>
#include <lodepng.h>
#include <File.h>
#include <Vector2d.h>
#include <Vec3d.h>
#include "Texture.h"
using namespace Glitter;
using namespace Glitter::Graphics;

Texture::Texture(std::string filename, float width, float height) :
        half_width(0.5f*width), half_height(0.5f*height),
        texture_handle(loadTexture(filename)), shader("assets/shaders/quad.vert", "assets/shaders/quad.frag") {

    float vertices[] = {
            -0.5f, -0.5f, 0.0f, // left
             0.5f, -0.5f, 0.0f, // right
             0.0f,  0.5f, 0.0f, // top
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

GLuint Texture::loadTexture(std::string filename){
    std::vector<unsigned char> image;
    unsigned error = lodepng::decode(image, width, height, filename);
    if(error != 0) {throw std::logic_error(lodepng_error_text(error));}

    u2 = 1; while(u2 < width) u2 *= 2;
    v2 = 1; while(v2 < height) v2 *= 2;
    // Ratio for power of two version compared to actual version, to render the non power of two image with proper size.
    u3 = (double)width / u2;
    v3 = (double)height / v2;

    // Make power of two version of the image.
    std::vector<unsigned char> image2(u2 * v2 * 4);
    for(size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            for (size_t c = 0; c < 4; c++) {
                image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];
            }
        }
    }

    glGenTextures(1, &texture_handle);
    glBindTexture(GL_TEXTURE_2D, texture_handle);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
//  glDisable(GL_ALPHA_TEST);
//
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image2[0]);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture_handle;
}
void Texture::render(Glitter::Math::Vec2d world_location, Glitter::Screen *s) {


    std::array<Math::Vec3d, 4> corners_world = {
            Math::Vec3d{-half_width+world_location.x,   half_width+world_location.y, 0.0},
            Math::Vec3d{ half_width+world_location.x,   half_width+world_location.y, 0.0},
            Math::Vec3d{ half_width+world_location.x,  -half_width+world_location.y, 0.0},
            Math::Vec3d{-half_width+world_location.x,  -half_width+world_location.y, 0.0}
    };
    for(auto& c : corners_world){
        auto c2d = s->convertWorldToRender({c.x, c.y});
        c.x = c2d.x;
        c.y = c2d.y;
    }

    shader.enable();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);


//    glColor4ub(255, 255, 255, 255);
//    glBindTexture(GL_TEXTURE_2D, texture_handle);
//    glEnable(GL_TEXTURE_2D);
//  glBegin(GL_QUADS);
//  glTexCoord2d(0.0, 0.0); glVertex2f(corners_world[0].x , corners_world[0].y);
//  glTexCoord2d( u3, 0.0); glVertex2f(corners_world[1].x , corners_world[1].y);
//  glTexCoord2d( u3,  v3); glVertex2f(corners_world[2].x , corners_world[2].y);
//  glTexCoord2d(0.0,  v3); glVertex2f(corners_world[3].x , corners_world[3].y);
//  glEnd();
//    glBindTexture(GL_TEXTURE_2D, 0);
//    glDisable(GL_TEXTURE_2D);
}
std::tuple<Math::Vec2d, Math::Vec2d> Texture::getBounds() const {
    return {Math::Vec2d{-half_width, -half_height}, Math::Vec2d{half_width, half_height}};
}

