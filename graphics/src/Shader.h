#pragma once
#include <GL/glew.h>

namespace Glitter {
namespace Graphics {
class Shader {

 public:
  Shader(const char* vertex_path, const char* fragment_path);
  void enable();
  void disable();
  GLuint getId();
  ~Shader();

 private:
  GLuint shaderID;
  const char* vertex_path;
  const char* fragment_path;

  GLuint load();
  void loadOne(const char* path, GLuint id);
};
}
}


