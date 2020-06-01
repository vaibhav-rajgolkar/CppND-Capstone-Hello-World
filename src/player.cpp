#include "player.h"
#include <algorithm>

void Player::updatePlayer(SDL_Texture* bulletTexture)
{
	if(reload_ > 0)
	{
		reload_--;
	}

	if(updatePosition_)
	{
		xDelta_ = 0;
		yDelta_ = 0;
		switch (direction_) 
		{
    		case Direction::kUp:
      			yDelta_ = -PLAYER_SPEED;
      			break;

    		case Direction::kDown:
      			yDelta_ = PLAYER_SPEED;
      			break;

    		case Direction::kLeft:
      			xDelta_ = -PLAYER_SPEED;
      			break;

    		case Direction::kRight:
      			xDelta_ = PLAYER_SPEED;
      			break;
  		}
		
		xPosition_ += xDelta_;
		yPosition_ += yDelta_;
	}

	if(fireBullet_ && reload_ == 0)
	{
		generateBullet(bulletTexture);
	}
}

void Player::generateBullet(SDL_Texture* bulletTexture)
{
	std::unique_ptr<Player> bullet = std::make_unique<Player>(this->xPosition_, this->yPosition_, bulletTexture, true);
	bullet->setDeltaX(PLAYER_BULLET_SPEED);
	//SDL_QueryTexture(bullet->texture_, NULL, NULL, &bullet->width_, &bullet->height_);
	bullet->yPosition_ += (this->height_ / 2) - (bullet->height_ / 2);

	this->reload_ = 8;
	bullets_.push_back(std::move(bullet));
}

