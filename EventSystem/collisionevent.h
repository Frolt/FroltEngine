#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "event.h"
#include "ECS/entity.h"

/**
   @brief The CollisionEvent struct stores information about the entities that collided
 */
struct CollisionEvent : public Event
{
    CollisionEvent(EntityID a, EntityID b);

    EntityID mEntityA;
    EntityID mEntityB;
};

#endif // COLLISIONEVENT_H
