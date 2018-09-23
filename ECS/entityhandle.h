#ifndef ENTITYHANDLE_H
#define ENTITYHANDLE_H

#include "entity.h"

// Forward declarations
class World;

struct EntityHandle
{
    EntityHandle() {}
    EntityHandle(World *world, Entity entity) : mWorld{world}, mEntity{entity} {}
    void destroy();
    template<typename T>
    void addComponent(T component);

    World *mWorld;
    Entity mEntity;
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

#include "world.h"

void EntityHandle::destroy()
{
    mWorld->destroyEntity(mEntity);
}

template<typename T>
void EntityHandle::addComponent(T component)
{
    mWorld->addComponent(mEntity, component);
}

#endif // ENTITYHANDLE_H
