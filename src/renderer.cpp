#include <iostream>
#include "constants.h"
#include "renderer.h"
#include "SDL2/SDL_mixer.h"

Renderer::Renderer()
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
}

  // Create Window
  sdl_window_ = SDL_CreateWindow("Space Shoot Game", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, Constant::kScreenWidth,
                                Constant::kScreenHeight, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window_) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  // Create renderer
  sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer_) {
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

Renderer::~Renderer() {
  SDL_DestroyTexture(playerTexture_);
  SDL_DestroyTexture(enemyTexture_);
  SDL_DestroyTexture(playerBulletTexture_);
  SDL_DestroyTexture(enemyBulletTexture_);
  SDL_DestroyTexture(backGroundTexture_);
  SDL_DestroyWindow(sdl_window_);
  SDL_Quit();
}

 void Renderer::RenderBackground() const
{
  if (--backgroundXposition_ < -Constant::kScreenWidth)
	{
		backgroundXposition_ = 0;
	}

	for (int x = backgroundXposition_ ; x < static_cast<int>(Constant::kScreenWidth) ; x += Constant::kScreenWidth)
	{
    SDL_Rect dest;
		dest.x = x;
		dest.y = 0;
		dest.w = Constant::kScreenWidth;
		dest.h = Constant::kScreenHeight;
		SDL_RenderCopy(sdl_renderer_, backGroundTexture_, NULL, &dest);
	}
}

void Renderer::Render(const Entity* player, const std::vector<std::unique_ptr<Entity>>& enemies) const 
{
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer_, /* 96, 128, 255, 255 */0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer_);

  // Render Background
  RenderBackground();

  // Render player
  Blit(player->getTexture(), player->getXPosition(), player->getYPosition());

 // Render Bullet
  for(const auto& bullet : player->bullets_)
  {
    Blit(bullet->getTexture(), bullet->getXPosition(), bullet->getYPosition());
  }

  // Render Enimies
  for(const auto& enemy : enemies)
  {
    Blit(enemy->getTexture(), enemy->getXPosition(), enemy->getYPosition());
    for(const auto& bullet : enemy->bullets_)
    {
      Blit(bullet->getTexture(), bullet->getXPosition(), bullet->getYPosition());
    }
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer_);
}

void Renderer::UpdateWindowTitle(int score, int fps) const {
  std::string title{"Score: " + std::to_string(score) + " Constant::kFPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window_, title.c_str());
}

void Renderer::Blit(SDL_Texture *texture, int x, int y) const
{
	SDL_Rect dest;
	
	dest.x = x;
	dest.y = y;
	int retval = SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
  //std::cout<<"Blit : "<<retval<<" : "<<SDL_GetError()<<std::endl;
	SDL_RenderCopy(sdl_renderer_, texture, NULL, &dest);
}

SDL_Texture *Renderer::LoadTexture(std::string filename) const
{
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename.c_str());

	texture = IMG_LoadTexture(sdl_renderer_, filename.c_str());

	return texture;
}