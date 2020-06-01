#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include <vector>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "player.h"


class Game {
 public:
  Game();
  ~Game();
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;

 private:

  std::unique_ptr<Player> player;
  std::vector<std::unique_ptr<Player>> enimies_;
  int score{0};
  int enemySpawnTimer_{0};

  void Update(Renderer &renderer);
  void UpdateEnimies();
  void fireBullets();
  void SpawnEnimies(Renderer &renderer);

  bool IsBulletHitEnimy(Player* bullet);

  int Collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
};

#endif