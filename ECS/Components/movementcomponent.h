#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include "a_math.h"
#include "ECS/component.h"

struct MovementComponent : public Component<MovementComponent>
{
    am::Vec3 mVelocity{0};
    float mAcceleration{0.0f};
};

#endif // MOVEMENTCOMPONENT_H
