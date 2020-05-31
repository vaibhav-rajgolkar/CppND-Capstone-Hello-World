#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "SDL.h"
#include <iostream>

class Player
{
public:

    enum class Direction { kUp, kDown, kLeft, kRight };

    Player(int x, int y, SDL_Texture* texture)
    :xPosition_(x),
    yPosition_(y),
    texture_(texture)
    {
    }

    ~Player() 
    {
        SDL_DestroyTexture(texture_);
    }

    int getXPosition() const { return xPosition_; }
    int getYPosition() const { return yPosition_; }
    SDL_Texture* getTexture() const { return texture_; }
    Direction getDirection() const { return direction_; }
    bool isPlayerAlive() const { return health_; }

    void setDirection(Direction dir) { direction_ = dir; }
    void setUpdatePosition(bool flag) { updatePosition_ = flag; }

    void UpdatePlayerPosition();


private:
    int xPosition_;
	int yPosition_;
    SDL_Texture *texture_;
    Direction direction_ = Direction::kUp;
    int speed_{4};
    bool health_{true};
    bool updatePosition_{false};
    bool fireBullet_{false};

    int xDelta;
    int yDelta;
};

#endif //PLAYER_H