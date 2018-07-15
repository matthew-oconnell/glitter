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
    if(game_window.isKeyPressed(GLFW_KEY_W) || game_window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
      glBegin(GL_TRIANGLES);
      float x = game_window.getCursorX();
      float y = game_window.getCursorY();
      float width = game_window.getWidth();
      float height = game_window.getHeight();
      float x_percent = x / width;
      float y_percent = -y / height;
      std::cout << "Cusor position " << x << " " << y << " percentages = " << x_percent << " " << y_percent << " width" << width << " height " << height << std::endl;
      x_percent -= 0.5;
      y_percent -= 0.5;
      glVertex2f(-0.1f+x_percent, -0.1f+y_percent);
      glVertex2f( 0.1f+x_percent,  0.1f+y_percent);
      glVertex2f( 0.1f+x_percent, -0.1f+y_percent);
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
