#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "SDL2/SDL_image.h"
#include "player.h"


class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Player* player);
  void UpdateWindowTitle(int score, int fps);
  void blit(SDL_Texture *texture, int x, int y);
  SDL_Texture *loadTexture(std::string filename);
  

  SDL_Renderer* getSdlRenderer() const { return sdl_renderer; }
  std::size_t getScreenWidth() const { return screen_width; }
  std::size_t getScreenHeight() const { return screen_height; }

  SDL_Texture* getPlayerTexture() const { return playerTexture_; }
  SDL_Texture* getEnemyTexture() const { return enimyTexture_; }
  SDL_Texture* getPlayerBulletTexture() const { return pBulletTexture_; }
  SDL_Texture* getEnemyBulletTexture() const { return eBulletTexture_; }


 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  SDL_Texture* playerTexture_;
  SDL_Texture* enimyTexture_;
  SDL_Texture* pBulletTexture_;
  SDL_Texture* eBulletTexture_;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif