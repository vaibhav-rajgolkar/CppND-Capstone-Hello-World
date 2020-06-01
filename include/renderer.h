#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "SDL2/SDL_image.h"
#include "entity.h"

class Renderer
{
public:
  Renderer();
  ~Renderer();

  // Disable copy construction and assignment operation
  Renderer(const Renderer &source) = delete;
  Renderer &operator=(const Renderer &source) = delete;

  Renderer(Renderer &&source);
  Renderer &operator=(Renderer &&source);

  void Render(const Entity *player, const std::vector<std::unique_ptr<Entity>> &enemies) const;
  void UpdateWindowTitle(int score, int fps) const;

  // getters
  SDL_Texture *GetPlayerTexture() const { return playerTexture_; }
  SDL_Texture *GetEnemyTexture() const { return enemyTexture_; }
  SDL_Texture *GetPlayerBulletTexture() const { return playerBulletTexture_; }
  SDL_Texture *GetEnemyBulletTexture() const { return enemyBulletTexture_; }

private:
  mutable int backgroundXposition_{0};

  SDL_Window *sdl_window_;
  SDL_Renderer *sdl_renderer_;

  SDL_Texture *playerTexture_;
  SDL_Texture *enemyTexture_;
  SDL_Texture *playerBulletTexture_;
  SDL_Texture *enemyBulletTexture_;
  SDL_Texture *backGroundTexture_;

  void RenderBackground() const;
  void Blit(SDL_Texture *texture, int x, int y) const;
  SDL_Texture *LoadTexture(std::string filename) const;
};

#endif