#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include "a_math.h"
#include "ECS/component.h"

struct MovementComponent : public Component<MovementComponent>
{
    MovementComponent() {}
    am::Vec3 mVelocity;
    float mAcceleration;
};

#endif // MOVEMENTCOMPONENT_H
