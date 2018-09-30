#ifndef ENTITYHANDLE_H
#define ENTITYHANDLE_H

#include "ECS/entity.h"

// Forward declarations
class World;

struct EntityHandle
{
    EntityHandle();
    EntityHandle(World *world, Entity entity);
    void destroy();
    template<typename T>
    void addComponent(const T &component);
    Entity &operator()();

    World *mWorld;
    Entity mEntity;
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

#include "world.h"

template<typename T>
void EntityHandle::addComponent(const T &component)
{
    mWorld->addComponent(mEntity, component);
}

#endif // ENTITYHANDLE_H
