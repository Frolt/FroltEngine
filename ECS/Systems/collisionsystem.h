#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "ECS/system.h"


/**
   @brief Checks if entities in the world collides, and published CollisionEvents accordingly
 */
class CollisionSystem : public System
{
public:
    CollisionSystem();
    void beginPlay() override;
    void update(float deltaTime) override;
    /// Check collisions by using the entities cube bounding box
    bool checkBoxCollision(EntityID entity1, EntityID entity2);
    /// Check collisions by using the entities sphere collision
    bool checkSphereCollision(EntityID entity1, EntityID entity2);
    /// Check if the entities height is below the terrain
    void checkTerrainCollision(EntityID entity);
};

#endif // COLLISIONSYSTEM_H
