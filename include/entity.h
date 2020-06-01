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

    Entity(int x, int y, SDL_Texture* texture, bool health, EntityType type);
    ~Entity();

    Entity(const Entity& source);
    Entity& operator=(const Entity& source);

    Entity(Entity&& source);
    Entity& operator=(Entity&& source);

    // getters
    float GetPositionX() const { return xPosition_; }
    float GetPositionY() const { return yPosition_; }
    float GetDeltaX() const { return xDelta_; }
    float GetDeltaY() const { return yDelta_; }
    int GetWidth() const { return width_; }
    int GetHeight() const { return height_; }
    SDL_Texture* GetTexture() const { return texture_; }
    Direction GetDirection() const { return direction_; }
    bool IsEntityAlive() const { return health_; }
    EntityType GetEntityType() const { return type_; }

    // setters
    void SetPositionX(float x) { xPosition_ = x; }
    void SetPositionY(float y) { yPosition_ = y; }
    void SetDeltaX(float x) { xDelta_ = x; }
    void SetHealth(bool health) { health_ = health; }
    void SetDirection(Direction dir) { direction_ = dir; }
    void SetUpdatePosition(bool flag) { updatePosition_ = flag; }
    void SetFireBullet(bool flag) { fireBullet_ = flag; }

    // utility
    void ClipPlayer();
    void UpdatePlayerMoves(SDL_Texture* bulletTexture);
    void GeneratePlayerBullet(SDL_Texture* bulletTexture);
    std::vector<std::unique_ptr<Entity>> bullets_{};

    void GenerateEnemyBullet(SDL_Texture* bulletTexture, Entity* player);
    void CalculateSlope(int x1, int y1, int x2, int y2, float &dx, float &dy);

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