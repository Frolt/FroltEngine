#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "ECS/system.h"

class MovementSystem : public System
{
public:
    MovementSystem();
    void init() override;
    void update(float deltaTime) override;
};

#endif // MOVEMENTSYSTEM_H
