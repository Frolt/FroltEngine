#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "a_math.h"
#include "ECS/component.h"

struct MovementComponent : public Component<MovementComponent>
{
    MovementComponent() {}
    MovementComponent(am::Vec3 velocity, float acceleration = 0)
        : mVelocity{velocity}, mAcceleration{acceleration} {}

    am::Vec3 mVelocity{0};
    float mAcceleration{0.0f};
};

#endif // MOVEMENT_COMPONENT_H
