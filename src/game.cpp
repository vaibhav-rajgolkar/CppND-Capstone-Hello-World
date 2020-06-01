#include "game.h"
#include <iostream>
#include <algorithm>
#include "SDL.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  player = std::make_unique<Player>(100, 100, renderer.getPlayerTexture(), true);

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, player.get());
    Update(renderer);
    renderer.Render(player.get(), enimies_);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update(Renderer &renderer) {
  if (!player->getHealth()) 
    return;

  player->updatePlayer(renderer.getPlayerBulletTexture());
  fireBullets();

  UpdateEnimies();
  SpawnEnimies(renderer);
}

void Game::UpdateEnimies()
{
  for(auto& enimy : enimies_)
  {
    enimy->setPositionX(enimy->getXPosition() + enimy->getDeltaX());
    enimy->setPositionY(enimy->getYPosition() + enimy->getDeltaY());
  }
  // Delete bullet objects which crosses screen
	enimies_.erase(
        std::remove_if( // Selectively remove elements in the second vector...
            enimies_.begin(),
            enimies_.end(),
            [&] (std::unique_ptr<Player> const& enimy)
            {   
                return (enimy->getXPosition() < enimy->getWidth() || enimy->getHealth() == 0);
            }),
        enimies_.end()
        );

}

void Game::fireBullets()
{
	for(auto& bullet : player->bullets_)
	{
		bullet->setPositionX(bullet->getXPosition() + bullet->getDeltaX());
    bullet->setPositionY(bullet->getYPosition() + bullet->getDeltaY());
	}

	// Delete bullet objects which crosses screen
	player->bullets_.erase(
        std::remove_if( // Selectively remove elements in the second vector...
            player->bullets_.begin(),
            player->bullets_.end(),
            [&] (std::unique_ptr<Player> const& p)
            {   
                return (p->getXPosition() > SCREEN_WIDTH || IsBulletHitEnimy(p.get()));
            }),
        player->bullets_.end()
        );
}

bool Game::IsBulletHitEnimy(Player* bullet)
{
  for(auto& enimy : enimies_)
  {
    if(Collision(bullet->getXPosition(), bullet->getYPosition(), bullet->getWidth(), bullet->getHeight(), 
                    enimy->getXPosition(), enimy->getYPosition(), enimy->getWidth(), enimy->getHeight()))
    {
      bullet->setHealth(false);
      enimy->setHealth(false);
      score++;
      return true;
    }
  }
  return false;
}


void Game::SpawnEnimies(Renderer &renderer)
{
  if (--enemySpawnTimer_ <= 0)
	{
    std::random_device dev;
    std::mt19937 engine(dev());
    std::uniform_int_distribution<int> randomHeightGenerator(0, 720);
    std::uniform_int_distribution<int> randomGenerator(0, 90);
  
    std::unique_ptr<Player> enemy = std::make_unique<Player>(1280, randomHeightGenerator(engine), renderer.getEnemyTexture(), true);
		enemy->setDeltaX(-(1 + (rand() % 2)));
    enimies_.push_back(std::move(enemy));

    enemySpawnTimer_ = 30 + randomGenerator(engine);
	}
}

int Game::Collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	return (std::max(x1, x2) < std::min(x1 + w1, x2 + w2)) && (std::max(y1, y2) < std::min(y1 + h1, y2 + h2));
}

int Game::GetScore() const { return score; }