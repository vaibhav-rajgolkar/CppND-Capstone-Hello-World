#include <iostream>
#include "SDL.h"

#include "controller.h"

 Controller::Controller(const Audio* audio)
 : audio_(audio)
 {
 }

 Controller::~Controller()
 {
     audio_ == nullptr;
 }

void Controller::ChangeDirection(Entity* player, Entity::Direction new_direction) const 
{
  player->setUpdatePosition(true);
  if (player->getDirection() != new_direction) player->setDirection(new_direction);
  return;
}

void Controller::HandleInput(bool &running , Entity* player) const {
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
          ChangeDirection(player, Entity::Direction::kUp);
          break;

        case SDLK_DOWN:
          ChangeDirection(player, Entity::Direction::kDown);
          break;

        case SDLK_LEFT:
          ChangeDirection(player, Entity::Direction::kLeft);
          break;

        case SDLK_RIGHT:
          ChangeDirection(player, Entity::Direction::kRight);
          break;
        
        case SDLK_LCTRL:
          player->setFireBullet(true);
          audio_->PlaySound(Audio::Sound::kSoundPlayerFire, Audio::Channel::kChannelPlayer);
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