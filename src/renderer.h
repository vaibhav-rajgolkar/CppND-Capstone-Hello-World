#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"


class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(/* Snake const snake, SDL_Point const &food */);
  void UpdateWindowTitle(int score, int fps);
  SDL_Texture *loadTexture(char *filename);
  void blit(SDL_Texture *texture, int x, int y);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif