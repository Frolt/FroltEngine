#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "ECS/system.h"


/**
   @brief The PhysicsSystem class adds gravity and physics,
    based on newtons second law, to all entities with a PhysicsComponent
 */
class PhysicsSystem : public System
{
public:
    PhysicsSystem();

    void beginPlay() override;
    void update(float deltaTime) override;
    void applyGravity(TransformComponent &transform, MovementComponent &movement);
};

#endif // PHYSICSSYSTEM_H
