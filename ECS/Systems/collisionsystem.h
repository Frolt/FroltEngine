#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "ECS/system.h"

class CollisionSystem : public System
{
public:
    CollisionSystem();
    void beginPlay() override;
    void update(float deltaTime) override;
    bool checkCollision(EntityID player, EntityID B);
};

#endif // COLLISIONSYSTEM_H
