#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "ECS/component.h"

struct CollisionComponent : public Component<CollisionComponent>
{
    CollisionComponent();
};

#endif // COLLISIONCOMPONENT_H
