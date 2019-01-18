#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Model.h"
#include "Square.h"
#include "Shader.h"

namespace Glitter::Graphics {
  class Texture : public Model {
  public:
      Texture(std::string filename, float width, float height);
      ~Texture();
      void render(Math::Vec2d world_location, Screen* s) override;
      std::tuple<Math::Vec2d, Math::Vec2d> getBounds() const override;

  private:
      float half_width, half_height;
      GLuint texture_handle;
      GLuint VAO, VBO, EBO;
      Shader shader;
      glm::vec3 origin[4];
      unsigned width, height;

      GLuint loadTexture(std::string filename);
      void initializeVertexData() ;
  };
}
