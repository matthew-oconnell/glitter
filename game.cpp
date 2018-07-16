#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Engine.h>
#include <Input.h>

void initialize();
void finalize();
void loop(Glitter::Core::Engine& engine);

int main() {
  initialize();

  Glitter::Core::Engine game_window("Glitter", 800, 600);
  glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

  loop(game_window);
  finalize();
  return 0;
}

void loop(Glitter::Core::Engine& engine) {
  while(!engine.closed()){
    engine.clear();
    Glitter::Core::Input* input = engine.getInput();
    if(input->isKeyPressed(GLFW_KEY_W) || input->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
      glBegin(GL_TRIANGLES);
      float x = input->getCursorX();
      float y = input->getCursorY();
      float width = float(engine.getWidth());
      float height = float(engine.getHeight());
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
    engine.update();
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
