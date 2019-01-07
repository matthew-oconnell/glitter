#include <GL/glew.h>
#include <stdexcept>
#include "GlewContext.h"
Glitter::Core::GlewContext::GlewContext() {
  glewExperimental = GL_TRUE;
  if( glewInit() != GLEW_OK){
    throw std::logic_error("Could not initialize GLEW!");
  }
}
