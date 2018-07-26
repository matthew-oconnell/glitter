#pragma once

#include <string>
#include <GL/glew.h>
#include "Model.h"
#include "Square.h"
namespace Glitter::Graphics {
class Texture : public Model {
 public:
  Texture(std::string filename, float width, float height);
  void render(Math::Vec2d world_location, Screen* s) override;
  std::tuple<Math::Vec2d, Math::Vec2d> getBounds() const override;

 private:
  float half_width, half_height;
  GLuint texture_handle;
  unsigned width, height;
  double u3, v3;
  size_t u2, v2;

  GLuint loadTexture(std::string filename);
};
}