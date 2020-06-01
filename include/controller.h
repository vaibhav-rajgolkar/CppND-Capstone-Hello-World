#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "entity.h"
#include "audio.h"

class Controller
{
public:
    Controller(const Audio *audio);
    ~Controller();

    // Disable copy construction and assignment
    Controller(const Controller &source) = delete;
    Controller &operator=(const Controller &source) = delete;

    Controller(Controller &&source);
    Controller &operator=(Controller &&source);

    void HandleInput(bool &running, Entity *player) const;

private:
    const Audio *audio_{nullptr};

    void ChangeDirection(Entity *player, Entity::Direction new_direction) const;
};

#endif