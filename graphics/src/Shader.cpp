#include <iostream>
#include <string>
#include "Shader.h"
#include <File.h>
using namespace Glitter;
using namespace Utilities;

Glitter::Graphics::Shader::Shader(const char *vertex_path, const char *fragment_path)
    : vertex_path(vertex_path), fragment_path(fragment_path) {

  printf("trying to open shader: %s %s", vertex_path, fragment_path);
  fflush(stdout);
  shaderID = load();
  enable();
}

GLuint Glitter::Graphics::Shader::load() {
  GLuint vertex_id = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
  loadOne(vertex_path, vertex_id);
  loadOne(fragment_path, fragment_id);

  GLuint program = glCreateProgram();
  glAttachShader(program, vertex_id);
  glAttachShader(program, fragment_id);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vertex_id);
  glDeleteShader(fragment_id);
  return program;
}
void Graphics::Shader::loadOne(const char *path, GLuint id) {
  std::string vertex_source = readFile(path);
  const char* v = vertex_source.c_str();

  glShaderSource(id, 1, &v, nullptr);
  glCompileShader(id);
  GLint result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if(result == GL_FALSE) {
    GLint length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    std::string error; error.resize(length);
    glGetShaderInfoLog(id, length, &length, error.data());
    std::cout << "Error building shader: " << std::endl << error << std::endl;
    glDeleteShader(id);
    throw std::logic_error("Could not compile shader: " + std::string(path));
  }
}
void Graphics::Shader::enable() {
  glUseProgram(shaderID);
}
void Graphics::Shader::disable() {
  glUseProgram(0);
}
Graphics::Shader::~Shader() {
  disable();
}
GLuint Graphics::Shader::getId() {
    return shaderID;
}
