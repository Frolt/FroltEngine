#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "ECS/system.h"

class CollisionSystem : public System
{
public:
    CollisionSystem();
    void beginPlay() override;
    void update(float deltaTime) override;
    bool checkCollision(EntityID entity1, EntityID entity2);
    void checkTerrainCollision(EntityID entity);
};

#endif // COLLISIONSYSTEM_H
