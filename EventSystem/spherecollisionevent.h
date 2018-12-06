#ifndef SPHERECOLLISIONEVENT_H
#define SPHERECOLLISIONEVENT_H

#include "event.h"
#include "ECS/entity.h"


struct SphereCollisionEvent : public Event
{
    SphereCollisionEvent(EntityID a, EntityID b);

    EntityID mEntityA;
    EntityID mEntityB;
};

#endif // SPHERECOLLISIONEVENT_H
