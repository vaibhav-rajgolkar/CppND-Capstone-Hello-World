#include <algorithm>

#include "constants.h"
#include "entity.h"

Entity::Entity(int x, int y, SDL_Texture *texture, bool health, EntityType type)
	: xPosition_(x),
	  yPosition_(y),
	  texture_(texture),
	  health_(health),
	  type_(type)
{
	SDL_QueryTexture(this->texture_, NULL, NULL, &this->width_, &this->height_);
}

Entity::~Entity()
{
	bullets_.erase(bullets_.begin(), bullets_.end());
	texture_ = NULL;
}

Entity::Entity(const Entity &source)
{
	xPosition_ = source.xPosition_;
	yPosition_ = source.yPosition_;
	xDelta_ = source.xDelta_;
	yDelta_ = source.yDelta_;

	width_ = source.width_;
	height_ = source.height_;

	reload_ = source.reload_;

	texture_ = source.texture_;

	direction_ = source.direction_;
	type_ = source.type_;

	health_ = source.health_;
	updatePosition_ = source.updatePosition_;
	fireBullet_ = source.fireBullet_;
}

Entity &Entity::operator=(const Entity &source)
{
	if (this == &source)
		return *this;

	xPosition_ = source.xPosition_;
	yPosition_ = source.yPosition_;
	xDelta_ = source.xDelta_;
	yDelta_ = source.yDelta_;

	width_ = source.width_;
	height_ = source.height_;

	reload_ = source.reload_;

	texture_ = source.texture_;

	direction_ = source.direction_;
	type_ = source.type_;

	health_ = source.health_;
	updatePosition_ = source.updatePosition_;
	fireBullet_ = source.fireBullet_;

	return *this;
}

Entity::Entity(Entity &&source)
{
	xPosition_ = source.xPosition_;
	yPosition_ = source.yPosition_;
	xDelta_ = source.xDelta_;
	yDelta_ = source.yDelta_;

	width_ = source.width_;
	height_ = source.height_;

	reload_ = source.reload_;

	texture_ = source.texture_;

	direction_ = source.direction_;
	type_ = source.type_;

	health_ = source.health_;
	updatePosition_ = source.updatePosition_;
	fireBullet_ = source.fireBullet_;

	source.xPosition_ = 0.0;
	source.yPosition_ = 0.0;
	source.xDelta_ = 0.0;
	source.yDelta_ = 0.0;
	source.width_ = 0;
	source.height_ = 0;
	source.reload_ = 0;
	source.texture_ = NULL;
}

Entity &Entity::operator=(Entity &&source)
{
	if (this == &source)
		return *this;

	xPosition_ = source.xPosition_;
	yPosition_ = source.yPosition_;
	xDelta_ = source.xDelta_;
	yDelta_ = source.yDelta_;

	width_ = source.width_;
	height_ = source.height_;

	reload_ = source.reload_;

	texture_ = source.texture_;

	direction_ = source.direction_;
	type_ = source.type_;

	health_ = source.health_;
	updatePosition_ = source.updatePosition_;
	fireBullet_ = source.fireBullet_;

	source.xPosition_ = 0.0;
	source.yPosition_ = 0.0;
	source.xDelta_ = 0.0;
	source.yDelta_ = 0.0;
	source.width_ = 0;
	source.height_ = 0;
	source.reload_ = 0;
	source.texture_ = NULL;
	return *this;
}

void Entity::UpdatePlayerMoves(SDL_Texture *bulletTexture)
{
	if (reload_ > 0)
	{
		reload_--;
	}

	if (updatePosition_)
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

	if (fireBullet_ && reload_ == 0)
	{
		GeneratePlayerBullet(bulletTexture);
	}
}

void Entity::GeneratePlayerBullet(SDL_Texture *bulletTexture)
{
	std::unique_ptr<Entity> bullet = std::make_unique<Entity>(this->xPosition_, this->yPosition_, bulletTexture, true, EntityType::kBullet);
	bullet->SetDeltaX(Constant::kPlayerBulletSpeed);
	//SDL_QueryTexture(bullet->texture_, NULL, NULL, &bullet->width_, &bullet->height_);
	bullet->yPosition_ += (this->height_ / 2) - (bullet->height_ / 2);

	this->reload_ = 8;
	bullets_.push_back(std::move(bullet));
}

void Entity::GenerateEnemyBullet(SDL_Texture *bulletTexture, Entity *player)
{
	if (--reload_ <= 0)
	{
		std::unique_ptr<Entity> bullet = std::make_unique<Entity>(this->xPosition_, this->yPosition_, bulletTexture, true, EntityType::kBullet);
		bullet->xPosition_ += (this->width_ / 2) - (bullet->width_ / 2);
		bullet->yPosition_ += (this->height_ / 2) - (bullet->height_ / 2);

		CalculateSlope(player->xPosition_ + (player->width_ / 2), player->yPosition_ + (player->height_ / 2), this->xPosition_,
					   this->yPosition_, bullet->xDelta_, bullet->yDelta_);

		bullet->xDelta_ *= Constant::kEnemyBulletSpeed;
		bullet->yDelta_ *= Constant::kEnemyBulletSpeed;

		this->reload_ = Constant::kFPS * (1 + rand() % 3);
		this->bullets_.push_back(std::move(bullet));
	}
}

void Entity::CalculateSlope(int x1, int y1, int x2, int y2, float &dx, float &dy)
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

void Entity::ClipPlayer()
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
