#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "ECS/system.h"

class PhysicsSystem : public System
{
public:
    PhysicsSystem();

    void beginPlay() override;
    void update(float deltaTime) override;
    void applyGravity(TransformComponent &transform, MovementComponent &movement);
};

#endif // PHYSICSSYSTEM_H
