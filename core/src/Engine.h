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
#include <Enemy.h>

struct GLFWwindow;

namespace Glitter {
namespace Core {

class GLFWInput;

class Engine {
 public:
  Engine(std::string title, int width, int height);
  void loop();
  void addPlayer(std::shared_ptr<Player::Player> p);
  void addEnemy(std::shared_ptr<Player::Enemy> e);
  void update();
  bool closed();
  GLFWInput* getInput();
  Window* getWindow();
  Screen* getScreen();
  void clear();
 private:
  std::string name;
  Screen screen;
  std::shared_ptr<Window> window;
  std::shared_ptr<GLFWInput> input;
  GlewContext glew_context;
  std::chrono::system_clock::time_point game_start;
  std::vector<std::shared_ptr<Player::Player>> players;
  std::vector<std::shared_ptr<Player::Enemy>> enemies;
  void drawStupiderCursor();
  void spawnEnemies(std::chrono::milliseconds game_time);
  void spawnRandomEnemy();
  void collidePlayersWithEnemies();
  bool collide(Player::Player *p, Player::Player *e);
  void drawCursor();
  void render();
};
}
}


