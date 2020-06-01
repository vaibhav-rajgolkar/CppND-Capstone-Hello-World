#include <iostream>
#include "constants.h"
#include "renderer.h"
#include "SDL2/SDL_mixer.h"

Renderer::Renderer()
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window_ = SDL_CreateWindow("Space War Game", SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, Constant::kScreenWidth,
                                 Constant::kScreenHeight, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window_)
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  // Create renderer
  sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer_)
  {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  playerTexture_ = LoadTexture("../graphics/player.png");
  enemyTexture_ = LoadTexture("../graphics/enemy.png");
  playerBulletTexture_ = LoadTexture("../graphics/playerBullet.png");
  enemyBulletTexture_ = LoadTexture("../graphics/alienBullet.png");
  backGroundTexture_ = LoadTexture("../graphics/background.png");

  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

Renderer::~Renderer()
{
  SDL_DestroyTexture(playerTexture_);
  SDL_DestroyTexture(enemyTexture_);
  SDL_DestroyTexture(playerBulletTexture_);
  SDL_DestroyTexture(enemyBulletTexture_);
  SDL_DestroyTexture(backGroundTexture_);
  SDL_DestroyWindow(sdl_window_);
  SDL_Quit();
}

Renderer::Renderer(Renderer &&source)
{
  backgroundXposition_ = source.backgroundXposition_;
  sdl_window_ = source.sdl_window_;
  sdl_renderer_ = source.sdl_renderer_;
  playerTexture_ = source.playerTexture_;
  enemyTexture_ = source.enemyTexture_;
  playerBulletTexture_ = source.playerBulletTexture_;
  enemyBulletTexture_ = source.enemyBulletTexture_;
  backGroundTexture_ = source.backGroundTexture_;

  source.backgroundXposition_ = 0;
  source.sdl_window_ = nullptr;
  source.sdl_renderer_ = nullptr;
  source.playerTexture_ = nullptr;
  source.enemyTexture_ = nullptr;
  source.playerBulletTexture_ = nullptr;
  source.enemyBulletTexture_ = nullptr;
  source.backGroundTexture_ = nullptr;
}

Renderer &Renderer::operator=(Renderer &&source)
{
  if (this == &source)
    return *this;

  backgroundXposition_ = source.backgroundXposition_;
  sdl_window_ = source.sdl_window_;
  sdl_renderer_ = source.sdl_renderer_;
  playerTexture_ = source.playerTexture_;
  enemyTexture_ = source.enemyTexture_;
  playerBulletTexture_ = source.playerBulletTexture_;
  enemyBulletTexture_ = source.enemyBulletTexture_;
  backGroundTexture_ = source.backGroundTexture_;

  source.backgroundXposition_ = 0;
  source.sdl_window_ = nullptr;
  source.sdl_renderer_ = nullptr;
  source.playerTexture_ = nullptr;
  source.enemyTexture_ = nullptr;
  source.playerBulletTexture_ = nullptr;
  source.enemyBulletTexture_ = nullptr;
  source.backGroundTexture_ = nullptr;

  return *this;
}

void Renderer::RenderBackground() const
{
  if (--backgroundXposition_ < -Constant::kScreenWidth)
  {
    backgroundXposition_ = 0;
  }

  for (int x = backgroundXposition_; x < static_cast<int>(Constant::kScreenWidth); x += Constant::kScreenWidth)
  {
    SDL_Rect dest;
    dest.x = x;
    dest.y = 0;
    dest.w = Constant::kScreenWidth;
    dest.h = Constant::kScreenHeight;
    SDL_RenderCopy(sdl_renderer_, backGroundTexture_, NULL, &dest);
  }
}

void Renderer::Render(const Entity *player, const std::vector<std::unique_ptr<Entity>> &enemies) const
{
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer_, /* 96, 128, 255, 255 */ 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer_);

  // Render Background
  RenderBackground();

  // Render player
  Blit(player->GetTexture(), player->GetPositionX(), player->GetPositionY());

  // Render Bullet
  for (const auto &bullet : player->bullets_)
  {
    Blit(bullet->GetTexture(), bullet->GetPositionX(), bullet->GetPositionY());
  }

  // Render Enimies
  for (const auto &enemy : enemies)
  {
    Blit(enemy->GetTexture(), enemy->GetPositionX(), enemy->GetPositionY());
    for (const auto &bullet : enemy->bullets_)
    {
      Blit(bullet->GetTexture(), bullet->GetPositionX(), bullet->GetPositionY());
    }
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer_);
}

void Renderer::UpdateWindowTitle(int score, int highscore) const
{
  std::string title{"*-- Mission SPACE WAR --*\t\tScore: " + std::to_string(score) + " <<===>> High Score: " + std::to_string(highscore)};
  SDL_SetWindowTitle(sdl_window_, title.c_str());
}

void Renderer::Blit(SDL_Texture *texture, int x, int y) const
{
  SDL_Rect dest;

  dest.x = x;
  dest.y = y;
  int retval = SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
  SDL_RenderCopy(sdl_renderer_, texture, NULL, &dest);
}

SDL_Texture *Renderer::LoadTexture(std::string filename) const
{
  SDL_Texture *texture;

  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename.c_str());

  texture = IMG_LoadTexture(sdl_renderer_, filename.c_str());

  return texture;
}