#pragma once
#include <string>
#include <map>
#include <GL/glew.h>

namespace Glitter {
class ModelDatabase {
 public:
  ModelDatabase() = default;
  void loadTexture(std::string filename, unsigned int width, unsigned int height);
  GLuint getTextureHandle(std::string filename);
 private:
  std::map<std::string, GLuint> textures;
};
}


