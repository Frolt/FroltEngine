#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "ECS/system.h"


/**
   @brief The MovementSystem class adds the entities velocity and acceleration to it's transform
 */
class MovementSystem : public System
{
public:
    MovementSystem();
    void beginPlay() override;
    void update(float deltaTime) override;
};

#endif // MOVEMENTSYSTEM_H
