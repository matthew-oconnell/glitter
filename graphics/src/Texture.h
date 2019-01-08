#pragma once

#include <string>
#include <GL/glew.h>
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
  unsigned width, height;
  double u3, v3;
  size_t u2, v2;

  GLuint loadTexture(std::string filename);
};
}
