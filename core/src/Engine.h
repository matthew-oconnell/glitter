#pragma once
#include <memory>
#include <string>
#include <array>
#include <chrono>
#include <Player.h>
#include <vector>
#include "GlewContext.h"
#include "Window.h"
#include <Screen.h>

struct GLFWwindow;

namespace Glitter {
namespace Core {

class Input;

class Engine {
 public:
  Engine(std::string title, int width, int height);
  void loop();
  void addPlayer(std::shared_ptr<Player::Player> p);
  void update();
  bool closed();
  Input* getInput();
  Window* getWindow();
  void clear();
 private:
  std::string name;
  Screen screen;
  std::shared_ptr<Window> window;
  std::shared_ptr<Input> input;
  GlewContext glew_context;
  std::chrono::system_clock::time_point game_start;
  std::vector<std::shared_ptr<Player::Player>> players;
  void drawStupiderCursor();
};
}
}


