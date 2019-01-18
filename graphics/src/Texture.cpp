#include <utility>

#include <string>
#include <lodepng.h>
#include <Vector2d.h>
#include <Vec3d.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glDebug.h>
#include "Texture.h"
using namespace Glitter;
using namespace Glitter::Graphics;

Texture::Texture(std::string filename, float width, float height) :
        half_width(0.5f*width), half_height(0.5f*height),
        shader("assets/shaders/quad.vert", "assets/shaders/quad.frag") {
    texture_handle = loadTexture(std::move(filename));
    initializeVertexData();
}
void Texture::initializeVertexData() {
    origin[0] = { half_width, half_height, 0.0f};
    origin[1] = { half_width,-half_height, 0.0f};
    origin[2] = {-half_width,-half_height, 0.0f};
    origin[3] = {-half_width, half_height, 0.0f};
    float vertices[] = {
            // positions          // texture coords
             half_width,  half_height, 0.0f,   1.0f, 1.0f, // top right
             half_width, -half_height, 0.0f,   1.0f, 0.0f, // bottom right
            -half_width, -half_height, 0.0f,   0.0f, 0.0f, // bottom left
            -half_width,  half_height, 0.0f,   0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

GLuint Texture::loadTexture(std::string filename){
    std::vector<unsigned char> image;
    unsigned error = lodepng::decode(image, width, height, filename);
    if(error != 0) {throw std::logic_error(lodepng_error_text(error));}

    size_t u2, v2;
    u2 = 1; while(u2 < width) u2 *= 2;
    v2 = 1; while(v2 < height) v2 *= 2;
    // Ratio for power of two version compared to actual version, to render the non power of two image with proper size.

    // Make power of two version of the image.
    std::vector<unsigned char> image2(u2 * v2 * 4);
    for(size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            for (size_t c = 0; c < 4; c++) {
                image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];
            }
        }
    }

    glCheckError();
    glGenTextures(1, &texture_handle);
    glCheckError();
    glBindTexture(GL_TEXTURE_2D, texture_handle);
    glCheckError();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image2[0]);
    glCheckError();
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    glCheckError();

    return texture_handle;
}
void Texture::render(Glitter::Math::Vec2d world_location, Glitter::Screen *s) {


    std::array<Math::Vec3d, 4> corners_world = {
            Math::Vec3d{-half_width+world_location.x,   half_width+world_location.y, 0.0},
            Math::Vec3d{ half_width+world_location.x,   half_width+world_location.y, 0.0},
            Math::Vec3d{ half_width+world_location.x,  -half_width+world_location.y, 0.0},
            Math::Vec3d{-half_width+world_location.x,  -half_width+world_location.y, 0.0}
    };
    world_location = s->convertWorldToRender(world_location);

    glCheckError();
    glActiveTexture(GL_TEXTURE0);
    glCheckError();
    glBindTexture(GL_TEXTURE_2D, texture_handle);
    glCheckError();
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
    trans = glm::translate(trans, glm::vec3(world_location.x, world_location.y, 0.0f));
    trans = glm::rotate(trans, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));
    shader.enable();
    unsigned int transformLoc = glGetUniformLocation(shader.getId(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    glCheckError();
    glBindVertexArray(VAO);
    glCheckError();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glCheckError();
}
std::tuple<Math::Vec2d, Math::Vec2d> Texture::getBounds() const {
    return {Math::Vec2d{-half_width, -half_height}, Math::Vec2d{half_width, half_height}};
}
Texture::~Texture() {
    glCheckError();
    glDeleteVertexArrays(1, &VAO);
    glCheckError();
    glDeleteBuffers(1, &VBO);
    glCheckError();
    glDeleteBuffers(1, &EBO);
    glCheckError();
}

