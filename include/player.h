#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>
#include <vector>
#include "SDL.h"
#include <iostream>

namespace
{
    constexpr int PLAYER_SPEED = 4;
    constexpr int BULLET_SPEED = 16;
    constexpr int SCREEN_WIDTH = 1280;
}
class Player
{
public:

    enum class Direction { kUp, kDown, kLeft, kRight };

    Player(int x, int y, SDL_Texture* texture, bool health)
    :xPosition_(x),
    yPosition_(y),
    texture_(texture),
    health_(health)
    {
        SDL_QueryTexture(this->texture_, NULL, NULL, &this->width_, &this->height_);
    }

    ~Player() 
    {
    }

    float getXPosition() const { return xPosition_; }
    float getYPosition() const { return yPosition_; }
    float getDeltaX() const { return xDelta_; }
    float getDeltaY() const { return yDelta_; }
    SDL_Texture* getTexture() const { return texture_; }
    Direction getDirection() const { return direction_; }
    bool getHealth() const { return health_; }
    bool isBulletFired() const { return fireBullet_; }

    void setPositionX(float x) { xPosition_ = x; }
    void setPositionY(float y) { yPosition_ = y; }
    void setDeltaX(float x) { xDelta_ = x; }
    void setDeltaY(float y) { yDelta_ = y; }
    void setHealth(bool health) { health_ = health; }
    void setDirection(Direction dir) { direction_ = dir; }
    void setUpdatePosition(bool flag) { updatePosition_ = flag; }
    void setFireBullet(bool flag) { fireBullet_ = flag; }

    void updatePlayer(SDL_Texture* bulletTexture);
    void generateBullet(SDL_Texture* bulletTexture);
    void fireBullets();
    std::vector<std::unique_ptr<Player>> bullets_{};

private:
    float xPosition_;
	float yPosition_;
    float xDelta_;
    float yDelta_;

    int width_;
    int height_;

    int reload_{0};

    SDL_Texture* texture_;

    Direction direction_ = Direction::kUp;

    bool health_{false};
    bool updatePosition_{false};
    bool fireBullet_{false};
};

#endif //PLAYER_H