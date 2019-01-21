#include <utility>
#include <vector>
#include <string>
#include <Vector2d.h>
#include <Vec3d.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glDebug.h>
#include "Texture.h"
using namespace Glitter;
using namespace Glitter::Graphics;

Texture::Texture(Utilities::ResourceManager& rm, std::string filename, float model_height, float model_width) :
        resource_manager(rm),
        half_width(0.5f*model_height), half_height(0.5f*model_width),
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
void Texture::render(Glitter::Math::Vec2d world_location, Glitter::Camera *s) {

    glCheckError();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_handle);
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(world_location.x, world_location.y, 0.0f));
    trans = glm::rotate(trans, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));
    shader.enable();
    auto [lo, hi] = s->rangeInWorldCoordinates();
    glm::mat4 projection = glm::ortho(lo.x, hi.x, lo.y, hi.y);
    glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "transform"), 1, GL_FALSE, glm::value_ptr(trans));
    glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glCheckError();
}
std::tuple<Math::Vec2d, Math::Vec2d> Texture::getWorldBounds() const {
    return {Math::Vec2d{-half_width, -half_height}, Math::Vec2d{half_width, half_height}};
}
Texture::~Texture() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

