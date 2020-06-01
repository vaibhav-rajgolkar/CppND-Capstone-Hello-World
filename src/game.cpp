#include "game.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include "SDL.h"

#include "constants.h"

Game::Game(const Audio *audio)
    : audio_(audio),
      currentScore_(0)
{
  ReadHighScoreFromCard();
}

Game::~Game()
{
  UpdateHighScoreToCard();
  enimies_.erase(enimies_.begin(), enimies_.end());
  audio_ = nullptr;
}

Game::Game(Game &&source)
    : player_(std::move(source.player_)),
      enimies_(std::move(source.enimies_))
{
  audio_ = source.audio_;
  currentScore_ = source.currentScore_;
  highScore_ = source.highScore_;
  enemySpawnTimer_ = source.enemySpawnTimer_;
  resetStageTime_ = source.resetStageTime_;

  source.audio_ = nullptr;
  source.currentScore_ = 0;
  source.highScore_ = 0;
  source.enemySpawnTimer_ = 0;
  source.resetStageTime_ = 0;
}

Game &Game::operator=(Game &&source)
{
  if (this == &source)
    return *this;

  audio_ = source.audio_;
  currentScore_ = source.currentScore_;
  highScore_ = source.highScore_;
  enemySpawnTimer_ = source.enemySpawnTimer_;
  resetStageTime_ = source.resetStageTime_;
  player_ = std::move(source.player_);
  enimies_ = std::move(source.enimies_);

  source.audio_ = nullptr;
  source.currentScore_ = 0;
  source.highScore_ = 0;
  source.enemySpawnTimer_ = 0;
  source.resetStageTime_ = 0;

  return *this;
}

void Game::ResetGame(const Renderer &renderer)
{
  player_ = std::make_unique<Entity>(Constant::kDefaultPlayerXPos, Constant::kDefaultPlayerYPos, renderer.GetPlayerTexture(), true, Entity::EntityType::kPlayer);
  enimies_.erase(enimies_.begin(), enimies_.end());
  enemySpawnTimer_ = 0;
  resetStageTime_ = Constant::kFPS * 2;
  currentScore_ = 0;
}

void Game::Run(const Controller &controller, const Renderer &renderer,
               std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  ResetGame(renderer);
  audio_->PlayMusic(true);

  while (running)
  {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, player_.get());
    Update(renderer);
    renderer.Render(player_.get(), enimies_);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000)
    {
      renderer.UpdateWindowTitle(currentScore_, highScore_);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update(const Renderer &renderer)
{
  //std::cout<<"resetStageTime : "<<resetStageTime_<<std::endl;

  if (!player_->IsEntityAlive() && --resetStageTime_ <= 0)
  {
    //update highscore
    highScore_ = currentScore_ > highScore_ ? currentScore_ : highScore_;

    ResetGame(renderer);
    audio_->PlayMusic(false);
  }

  player_->UpdatePlayerMoves(renderer.GetPlayerBulletTexture());
  FireBullets(player_.get());
  player_->ClipPlayer();

  UpdateEnimies();
  FireEnimyBullets(renderer);
  SpawnEnimies(renderer);
}

void Game::UpdateEnimies()
{
  for (auto &enimy : enimies_)
  {
    enimy->SetPositionX(enimy->GetPositionX() + enimy->GetDeltaX());
    enimy->SetPositionY(enimy->GetPositionY() + enimy->GetDeltaY());
  }
  // Delete enimy objects which crosses screen or hit by player bullet
  enimies_.erase(
      std::remove_if( // Selectively remove elements in the second vector...
          enimies_.begin(),
          enimies_.end(),
          [&](std::unique_ptr<Entity> const &enimy) {
            return (enimy->GetPositionX() < -enimy->GetWidth() || enimy->IsEntityAlive() == 0);
          }),
      enimies_.end());
}

void Game::FireBullets(Entity *entity)
{
  for (auto &bullet : entity->bullets_)
  {
    bullet->SetPositionX(bullet->GetPositionX() + bullet->GetDeltaX());
    bullet->SetPositionY(bullet->GetPositionY() + bullet->GetDeltaY());
  }

  // Delete bullet objects which crosses screen
  entity->bullets_.erase(
      std::remove_if( // Selectively remove elements in the second vector...
          entity->bullets_.begin(),
          entity->bullets_.end(),
          [&](std::unique_ptr<Entity> const &p) {
            return (p->GetPositionX() > Constant::kScreenWidth || p->GetPositionY() > Constant::kScreenHeight || p->GetPositionX() < -p->GetWidth() || p->GetPositionY() < -p->GetHeight() || IsBulletHitEntity(p.get(), entity));
          }),
      entity->bullets_.end());
}

bool Game::IsBulletHitEntity(Entity *bullet, Entity *entity)
{
  if (entity->GetEntityType() == Entity::EntityType::kPlayer)
  {
    for (auto &enimy : enimies_)
    {
      if (Collision(bullet->GetPositionX(), bullet->GetPositionY(), bullet->GetWidth(), bullet->GetHeight(),
                    enimy->GetPositionX(), enimy->GetPositionY(), enimy->GetWidth(), enimy->GetHeight()))
      {
        audio_->PlaySound(Audio::Sound::kSoundEnemyDie, Audio::Channel::kChannleAny);
        bullet->SetHealth(false);
        enimy->SetHealth(false);
        currentScore_++;
        return true;
      }
    }
  }
  else if (entity->GetEntityType() == Entity::EntityType::kEnimy)
  {
    if (Collision(bullet->GetPositionX(), bullet->GetPositionY(), bullet->GetWidth(), bullet->GetHeight(),
                  player_->GetPositionX(), player_->GetPositionY(), player_->GetWidth(), player_->GetHeight()))
    {
      audio_->PlaySound(Audio::Sound::kSoundPlayerDie, Audio::Channel::kChannelPlayer);
      bullet->SetHealth(false);
      player_->SetHealth(false);
      return true;
    }
  }
  return false;
}

void Game::SpawnEnimies(const Renderer &renderer)
{
  if (--enemySpawnTimer_ <= 0)
  {
    std::random_device dev;
    std::mt19937 engine(dev());
    std::uniform_int_distribution<int> randomHeightGenerator(0, Constant::kScreenHeight);
    std::uniform_int_distribution<int> randomGenerator(0, 90);

    std::unique_ptr<Entity> enemy = std::make_unique<Entity>(Constant::kScreenWidth, randomHeightGenerator(engine), renderer.GetEnemyTexture(), true, Entity::EntityType::kEnimy);
    enemy->SetDeltaX(-(1 + (rand() % 2)));
    enimies_.push_back(std::move(enemy));

    enemySpawnTimer_ = 60 + randomGenerator(engine);
  }
}

void Game::FireEnimyBullets(const Renderer &renderer)
{
  for (auto &enimy : enimies_)
  {
    enimy->GenerateEnemyBullet(renderer.GetEnemyBulletTexture(), player_.get());
    FireBullets(enimy.get());
  }
}

int Game::Collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) const
{
  return (std::max(x1, x2) < std::min(x1 + w1, x2 + w2)) && (std::max(y1, y2) < std::min(y1 + h1, y2 + h2));
}

void Game::UpdateHighScoreToCard()
{
  std::ofstream filestream("../score/scorecard.txt", std::ios::trunc);
  if (filestream.is_open())
  {
    filestream << "highscore " << std::to_string(highScore_);
    filestream.close();
  }
}

int Game::ReadHighScoreFromCard()
{
  std::ifstream filestream("../score/scorecard.txt");
  if (filestream.is_open())
    ;
  {
    std::string line{}, token{};
    int value;

    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> token >> value;

    if (token == "highscore")
    {
      //std::cout<<"highscore read from file : "<<value<<std::endl;
      highScore_ = value;
    }
  }
}