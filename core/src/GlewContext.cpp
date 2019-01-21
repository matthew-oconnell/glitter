#include <stdio.h>
#include <GL/glew.h>
#include <stdexcept>
#include "GlewContext.h"

void GLAPIENTRY MessageCallback( GLenum source,
                                 GLenum type,
                                 GLuint id,
                                 GLenum severity,
                                 GLsizei length,
                                 const GLchar* message,
                                 const void* userParam ) {

  printf("GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
           type, severity, message );
}

Glitter::GlewContext::GlewContext() {
  printf("Initializing Glew...\n"); fflush(stdout);
  glewExperimental = GL_TRUE;
  if( glewInit() != GLEW_OK){
    throw std::logic_error("Could not initialize GLEW!");
  } else {
    printf("GLEW initialized.\n");
    printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
    fflush(stdout);
  }
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
}
