
#include <window.h>
#include <GLFW/glfw3.h>
#include <iostream>

void initialize();
void finalize();
void loop(Glitter::Graphics::Window& game_window);

int main() {
  initialize();

  Glitter::Graphics::Window game_window("Glitter", 800, 600);
  glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

  loop(game_window);

  finalize();
}

void loop(Glitter::Graphics::Window& game_window) {
  while(!game_window.closed()){
    game_window.clear();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f( 0.5f,  0.5f);
    glVertex2f( 0.5f, -0.5f);
    glEnd();
    game_window.update();
  }
}

void initialize() {
  if( !glfwInit())
    throw std::logic_error("Could not initialize GLFW!");
  std::cout << glGetString(GL_VERSION);
}
void finalize() {
  glfwTerminate();
}
