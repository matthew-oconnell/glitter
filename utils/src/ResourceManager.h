#pragma once
#include <string>
#include <map>
#include <GL/glew.h>

namespace Glitter {
namespace Utilities {
class ResourceManager {
 public:
  ResourceManager() = default;
  void loadTexture(std::string filename, unsigned int width, unsigned int height);
  GLuint getTextureHandle(std::string filename);
 private:
  std::map<std::string, GLuint> textures;
};
}
}


