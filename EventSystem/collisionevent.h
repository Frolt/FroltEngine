#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "event.h"
#include "ECS/entity.h"

struct CollisionEvent : public Event
{
    CollisionEvent(Entity *a, Entity *b);

    Entity *mEntityA;
    Entity *mEntityB;
};

#endif // COLLISIONEVENT_H
