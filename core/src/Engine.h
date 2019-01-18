#pragma once
#include <memory>
#include <string>
#include <array>
#include <chrono>
#include <vector>

#include "GlewContext.h"
#include "Window.h"

#include <Player.h>
#include <Screen.h>
#include <Enemy.h>
#include <Bullet.h>
#include <Ally.h>
#include <Text.h>

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
  GlewContext glew_context;
  std::shared_ptr<GLFWInput> input;
  Text text;
  std::chrono::system_clock::time_point game_start;
  std::vector<std::shared_ptr<Player::Ally>> allies;
  std::vector<std::shared_ptr<Player::Enemy>> enemies;
  std::vector<std::shared_ptr<Player::Bullet>> bullets;
  void spawnEnemies(std::chrono::milliseconds game_time);
  void spawnRandomEnemy();
  void collidePlayersWithEnemies();
  bool collide(Player::Player *p, Player::Player *e);
  void render();
  void collideBulletsWithEnemies();
  void flashScreenRed();
  void setScreenColorBlack();
  void playerDies(Player::Ally* p);
  void resetEnemies();
  void drawEnemies();
  void drawBullets();
  void drawPlayers();
};
}
}


