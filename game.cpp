#include <window.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void initialize();
void finalize();
void loop(Glitter::Graphics::Window& game_window);

int main() {
  initialize();

  Glitter::Graphics::Window game_window("Glitter", 800, 600);
  glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  loop(game_window);
  finalize();
  return 0;
}

void loop(Glitter::Graphics::Window& game_window) {
  while(!game_window.closed()){
    game_window.clear();
    if(game_window.isKeyPressed(GLFW_KEY_W)) {
      glBegin(GL_TRIANGLES);
      glVertex2f(-0.5f, -0.5f);
      glVertex2f( 0.5f,  0.5f);
      glVertex2f( 0.5f, -0.5f);
      glEnd();
    }
//    glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
    game_window.update();
  }
}

void initialize() {
  std::cout << "Initializing Glitter" << std::endl;
  if( !glfwInit())
    throw std::logic_error("Could not initialize GLFW!");
  std::cout << "glfw initialized" << std::endl;
}
void finalize() {
  glfwTerminate();
}
