#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <memory>
#include <vector>
#include "SDL.h"
#include <iostream>

class Entity
{
public:

    enum class Direction { kUp, kDown, kLeft, kRight };
    enum class EntityType { kPlayer, kEnimy, kBullet, kInvalid};

    Entity(int x, int y, SDL_Texture* texture, bool health, EntityType type)
    :xPosition_(x),
    yPosition_(y),
    texture_(texture),
    health_(health),
    type_(type)
    {
        SDL_QueryTexture(this->texture_, NULL, NULL, &this->width_, &this->height_);
    }

    ~Entity() 
    {
        bullets_.erase(bullets_.begin(), bullets_.end());
        texture_ = NULL;
    }

    // getters
    float getXPosition() const { return xPosition_; }
    float getYPosition() const { return yPosition_; }
    float getDeltaX() const { return xDelta_; }
    float getDeltaY() const { return yDelta_; }
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    SDL_Texture* getTexture() const { return texture_; }
    Direction getDirection() const { return direction_; }
    bool getHealth() const { return health_; }
    EntityType getEntityType() const { return type_; }

    // setters
    void setPositionX(float x) { xPosition_ = x; }
    void setPositionY(float y) { yPosition_ = y; }
    void setDeltaX(float x) { xDelta_ = x; }
    void setHealth(bool health) { health_ = health; }
    void setDirection(Direction dir) { direction_ = dir; }
    void setUpdatePosition(bool flag) { updatePosition_ = flag; }
    void setFireBullet(bool flag) { fireBullet_ = flag; }

    // utility
    void clipPlayer();
    void updatePlayer(SDL_Texture* bulletTexture);
    void generatePlayerBullet(SDL_Texture* bulletTexture);
    std::vector<std::unique_ptr<Entity>> bullets_{};

    void generateEnimyBullet(SDL_Texture* bulletTexture, Entity* player);
    void calcSlope(int x1, int y1, int x2, int y2, float &dx, float &dy);

private:
    float xPosition_;
	float yPosition_;
    float xDelta_;
    float yDelta_;

    int width_;
    int height_;

    int reload_{0};

    SDL_Texture* texture_;

    Direction direction_{ Direction::kUp };
    EntityType type_{ EntityType::kInvalid };

    bool health_{false};
    bool updatePosition_{false};
    bool fireBullet_{false};
};

#endif //ENTITY_H