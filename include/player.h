#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "SDL.h"
#include <iostream>

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
    }

    ~Player() 
    {
        SDL_DestroyTexture(texture_);
    }

    int getXPosition() const { return xPosition_; }
    int getYPosition() const { return yPosition_; }
    int getDeltaX() const { return xDelta_; }
    int getDeltaY() const { return yDelta_; }
    SDL_Texture* getTexture() const { return texture_; }
    Direction getDirection() const { return direction_; }
    bool getHealth() const { return health_; }
    bool isBulletFired() const { return fireBullet_; }

    void setPositionX(int x) { xPosition_ = x; }
    void setPositionY(int y) { yPosition_ = y; }
    void setDeltaX(int x) { xDelta_ = x; }
    void setDeltaY(int y) { yDelta_ = y; }
    void setHealth(bool health) { health_ = health; }
    void setDirection(Direction dir) { direction_ = dir; }
    void setUpdatePosition(bool flag) { updatePosition_ = flag; }
    void setFireBullet(bool flag) { fireBullet_ = flag; }

    void UpdatePlayerPosition();


private:
    int xPosition_;
	int yPosition_;
    SDL_Texture *texture_;
    Direction direction_ = Direction::kUp;
    int speed_{4};
    bool health_{false};
    bool updatePosition_{false};
    bool fireBullet_{false};

    int xDelta_;
    int yDelta_;
};

#endif //PLAYER_H