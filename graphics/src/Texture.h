#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ResourceManager.h>
#include "Model.h"
#include "Square.h"
#include "Shader.h"

namespace Glitter::Graphics {
  class Texture : public Model {
  public:
      Texture(Glitter::Utilities::ResourceManager& resource_manager, std::string filename, float width, float height);
      ~Texture();
      void render(Math::Vec2d world_location, Screen* s) override;
      std::tuple<Math::Vec2d, Math::Vec2d> getBounds() const override;

  private:
      Glitter::Utilities::ResourceManager& resource_manager;
      float half_width, half_height;
      GLuint texture_handle;
      GLuint VAO, VBO, EBO;
      Shader shader;
      unsigned width, height;

      GLuint getTexture(std::string filename);
      void initializeVertexData() ;
  };
}
