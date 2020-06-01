#include <algorithm>

#include "constants.h"
#include "entity.h"

void Entity::updatePlayer(SDL_Texture* bulletTexture)
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
      			yDelta_ = -Constant::kPlayerSpeed;
      			break;

    		case Direction::kDown:
      			yDelta_ = Constant::kPlayerSpeed;
      			break;

    		case Direction::kLeft:
      			xDelta_ = -Constant::kPlayerSpeed;
      			break;

    		case Direction::kRight:
      			xDelta_ = Constant::kPlayerSpeed;
      			break;
  		}
		
		xPosition_ += xDelta_;
		yPosition_ += yDelta_;
	}

	if(fireBullet_ && reload_ == 0)
	{
		generatePlayerBullet(bulletTexture);
	}
}

void Entity::generatePlayerBullet(SDL_Texture* bulletTexture)
{
	std::unique_ptr<Entity> bullet = std::make_unique<Entity>(this->xPosition_, this->yPosition_, bulletTexture, true, EntityType::kBullet);
	bullet->setDeltaX(Constant::kPlayerBulletSpeed);
	//SDL_QueryTexture(bullet->texture_, NULL, NULL, &bullet->width_, &bullet->height_);
	bullet->yPosition_ += (this->height_ / 2) - (bullet->height_ / 2);

	this->reload_ = 8;
	bullets_.push_back(std::move(bullet));
}

void Entity::generateEnimyBullet(SDL_Texture* bulletTexture, Entity* player)
{
	if(--reload_ <= 0)
	{
		std::unique_ptr<Entity> bullet = std::make_unique<Entity>(this->xPosition_, this->yPosition_, bulletTexture, true, EntityType::kBullet);
		bullet->xPosition_ += (this->width_/ 2) - (bullet->width_ / 2);
		bullet->yPosition_ += (this->height_ / 2) - (bullet->height_ / 2);

		calcSlope(player->xPosition_ + (player->width_ / 2), player->yPosition_ + (player->height_ / 2), this->xPosition_, 
					this->yPosition_, bullet->xDelta_, bullet->yDelta_);
		
		bullet->xDelta_ *= Constant::kEnemyBulletSpeed;
		bullet->yDelta_ *= Constant::kEnemyBulletSpeed;

		this->reload_ = Constant::kFPS * (1 + rand() % 3);
		this->bullets_.push_back(std::move(bullet));
	}

}

void Entity::calcSlope(int x1, int y1, int x2, int y2, float &dx, float &dy)
{
	int steps = std::max(abs(x1 - x2), abs(y1 - y2));

	if (steps == 0)
	{
		dx = dy = 0;
		return;
	}

	dx = (x1 - x2);
	dx /= steps;

	dy = (y1 - y2);
	dy /= steps;
}

void Entity::clipPlayer()
{
	if (this->xPosition_ < 0)
	{
		this->xPosition_ = 0;
	}
	
	if (this->yPosition_ < 0)
	{
		this->yPosition_ = 0;
	}
	
	if (this->xPosition_ > Constant::kScreenWidth / 2)
	{
		this->xPosition_ = Constant::kScreenWidth / 2;
	}
	
	if (this->yPosition_ > Constant::kScreenHeight - this->height_)
	{
		this->yPosition_ = Constant::kScreenHeight - this->height_;
	}
}
