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
#include <Bullet.h>
#include <Ally.h>

struct GLFWwindow;

namespace Glitter {
namespace Core {

class GLFWInput;

class Engine {
 public:
  Engine(std::string title);
  void loop();
  void addAlly(std::shared_ptr<Player::Ally> p);
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
  std::vector<std::shared_ptr<Player::Ally>> allies;
  std::vector<std::shared_ptr<Player::Enemy>> enemies;
  std::vector<std::shared_ptr<Player::Bullet>> bullets;
  void spawnEnemies(std::chrono::milliseconds game_time);
  void spawnRandomEnemy();
  void collidePlayersWithEnemies();
  bool collide(Player::Player *p, Player::Player *e);
  void drawCursor();
  void render();
  void drawAim();
  void collideBulletsWithEnemies();
  void flashScreenRed();
  void setScreenColorBlue();
  void playerDies(Player::Ally* p);
  void resetEnemies();
  void drawEnemies();
  void drawBullets();
  void drawPlayers();
};
}
}


