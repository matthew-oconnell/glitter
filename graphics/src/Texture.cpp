#include <utility>
#include <vector>
#include <string>
#include <Vector2d.h>
#include <Vec3d.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glDebug.h>
#include "Texture.h"
using namespace Glitter;
using namespace Glitter::Graphics;

Texture::Texture(Utilities::ResourceManager& rm, std::string filename, float width, float height) :
        resource_manager(rm),
        half_width(0.5f*width), half_height(0.5f*height),
        shader("assets/shaders/quad.vert", "assets/shaders/quad.frag") {
    texture_handle = getTexture(std::move(filename));
    initializeVertexData();
}
void Texture::initializeVertexData() {
    float vertices[] = {
            // positions          // texture coords
            -half_width, -half_height, 0.0f, 0.0f, 0.0f, // bottom left
             half_width, -half_height, 0.0f, 1.0f, 0.0f, // bottom right
             half_width,  half_height, 0.0f, 1.0f, 1.0f, // top right
            -half_width,  half_height, 0.0f, 0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
            0, 1, 2, // first triangle
            2, 3, 0  // second triangle
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

GLuint Texture::getTexture(std::string filename){
  resource_manager.loadTexture(filename, width, height);
  return resource_manager.getTextureHandle(filename);
}
void Texture::render(Glitter::Math::Vec2d world_location, Glitter::Screen *s) {

    world_location = s->convertWorldToRender(world_location);

    glCheckError();
    glActiveTexture(GL_TEXTURE0);
    glCheckError();
    glBindTexture(GL_TEXTURE_2D, texture_handle);
    glCheckError();
    glm::mat4 trans = glm::mat4(1.0f);
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
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

