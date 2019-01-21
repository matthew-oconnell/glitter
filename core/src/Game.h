#pragma once
#include <memory>
#include <string>
#include <array>
#include <chrono>
#include <vector>

#include "GlewContext.h"
#include "Engine.h"

#include <Player.h>
#include <Camera.h>
#include <Enemy.h>
#include <Bullet.h>
#include <PowerUp.h>
#include <Ally.h>
#include <Text.h>

struct GLFWwindow;

namespace Glitter {
namespace Core {

class GLFWInput;

class Game {
 public:
  Game(std::string title);
  void loop();
  void addAlly(std::shared_ptr<Player::Ally> p);
  void addEnemy(std::shared_ptr<Player::Enemy> e);
  void update();
  bool closed();
  Engine* getEngine();
  void clear();
 private:
  std::string name;
  Engine engine;
  Text text;
  Utilities::ResourceManager resource_manager;
  unsigned int score = 0;
  unsigned int high_score = 0;
  std::chrono::system_clock::time_point game_start;
  std::vector<std::shared_ptr<Player::Ally>> allies;
  std::vector<std::shared_ptr<Player::Enemy>> enemies;
  std::vector<std::shared_ptr<Player::Bullet>> bullets;
  std::vector<std::shared_ptr<Player::PowerUp>> power_ups;
  void spawnEnemies(std::chrono::milliseconds game_time);
  void spawnPowerUps(std::chrono::milliseconds game_time);
  void spawnRandomEnemy();
  void collidePlayersWithEnemies();
  void collideBulletsWithEnemies();
  void collidePlayersWithPowerUps();
  bool collide(Player::Player *p, Player::Player *e);
  void render();
  void flashScreenRed();
  void setScreenColorBlack();
  void playerDies(Player::Ally* p);
  void clearAllEnemies();
  void drawEnemies();
  void drawBullets();
  void drawPlayers();
  void drawPowerUps();
  void clearAllPowerUps();
};
}
}


