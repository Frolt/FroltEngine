#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "ECS/component.h"


struct PhysicsComponent : public Component<PhysicsComponent>
{
    PhysicsComponent();
};

#endif // PHYSICS_COMPONENT_H
