#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include "ECS/component.h"
#include "a_math.h"

struct CollisionComponent : public Component<CollisionComponent>
{
    CollisionComponent();

    am::Vec3 mSize{1};
};

#endif // COLLISION_COMPONENT_H
