#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include <vector>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "entity.h"
#include "audio.h"


class Game {
 public:
  Game(const Audio* audio);
  ~Game();
  
  void Run(Controller const& controller, const Renderer& renderer,
           std::size_t target_frame_duration);
  int GetScore() const;

 private:

  // data members
  const Audio* audio_{nullptr};
  int score{0};
  int enemySpawnTimer_{0};
  int resetStageTime_{0};
  std::unique_ptr<Entity> player_;
  std::vector<std::unique_ptr<Entity>> enimies_;

  // utility
  void ResetGame(const Renderer& renderer);
  void Update(const Renderer& renderer);
  void FireBullets(Entity* entity);
  void SpawnEnimies(const Renderer& renderer);
  void UpdateEnimies();
  void FireEnimyBullets(const Renderer& renderer);
  bool IsBulletHitEntity(Entity* bullet, Entity* entity);
  int Collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) const;
 
 
};

#endif