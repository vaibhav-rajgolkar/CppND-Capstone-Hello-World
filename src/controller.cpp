#include "controller.h"
#include <iostream>
#include "SDL.h"


void Controller::ChangeDirection(Player* player, Player::Direction newDirection) const 
{
  player->setUpdatePosition(true);
  if (player->getDirection() != newDirection) player->setDirection(newDirection);
  return;
}

void Controller::HandleInput(bool &running , Player* player) const {
  SDL_Event event;
  while (SDL_PollEvent(&event)) 
  {
    if (event.type == SDL_QUIT) 
    {
      running = false;
    } 
    else if (event.type == SDL_KEYDOWN) 
    {
      switch (event.key.keysym.sym) 
      {
        case SDLK_UP:
          ChangeDirection(player, Player::Direction::kUp);
          break;

        case SDLK_DOWN:
          ChangeDirection(player, Player::Direction::kDown);
          break;

        case SDLK_LEFT:
          ChangeDirection(player, Player::Direction::kLeft);
          break;

        case SDLK_RIGHT:
          ChangeDirection(player, Player::Direction::kRight);
          break;
        
        case SDLK_LCTRL:
          player->setFireBullet(true);
          break;
      }
    }
    else if (event.type == SDL_KEYUP )
    {
      switch (event.key.keysym.sym) 
      {
        case SDLK_UP:
        case SDLK_DOWN:
        case SDLK_LEFT:
        case SDLK_RIGHT:
          player->setUpdatePosition(false);
          break;
        
        case SDLK_LCTRL:
          player->setFireBullet(false);
          break;
      }
    }
  }
}