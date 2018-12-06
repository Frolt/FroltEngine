#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "a_math.h"
#include "ECS/component.h"


struct MovementComponent : public Component<MovementComponent>
{
    MovementComponent(const am::Vec3 &velocity = {0}, float acceleration = 0);

    am::Vec3 mVelocity;
    float mAcceleration;
};

#endif // MOVEMENT_COMPONENT_H
