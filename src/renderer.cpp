#include <iostream>
#include "renderer.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Space Shoot Game", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  playerTexture_ = loadTexture("../graphics/player.png");
  enimyTexture_ = loadTexture("../graphics/enemy.png");
  pBulletTexture_ = loadTexture("../graphics/playerBullet.png");
  eBulletTexture_ = loadTexture("../graphics/alienBullet.png");

  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

Renderer::~Renderer() {
  SDL_DestroyTexture(playerTexture_);
  SDL_DestroyTexture(enimyTexture_);
  SDL_DestroyTexture(pBulletTexture_);
  SDL_DestroyTexture(eBulletTexture_);
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Player* player) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 96, 128, 255, 255/* 0x1E, 0x1E, 0x1E, 0xFF */);
  SDL_RenderClear(sdl_renderer);

  // Render player
  blit(player->getTexture(), player->getXPosition(), player->getYPosition());

 // Render Bullet
  for(const auto& bullet : player->bullets_)
  {
    blit(bullet->getTexture(), bullet->getXPosition(), bullet->getYPosition());
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::blit(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest;
	
	dest.x = x;
	dest.y = y;
	int retval = SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	
	SDL_RenderCopy(sdl_renderer, texture, NULL, &dest);
}

SDL_Texture *Renderer::loadTexture(std::string filename)
{
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename.c_str());

	texture = IMG_LoadTexture(sdl_renderer, filename.c_str());

	return texture;
}