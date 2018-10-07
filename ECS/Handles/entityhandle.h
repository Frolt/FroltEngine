#ifndef ENTITYHANDLE_H
#define ENTITYHANDLE_H

#include "ECS/entity.h"

// Forward declarations
class World;

struct EntityHandle
{
    EntityHandle() = default;
    EntityHandle(World *world, const Entity &entity);
    void destroy();
    template<typename T>
    void addComponent(const T &component);
    template<typename T>
    void removeComponent();
    Entity &operator()();
    const Entity &operator()() const;

public:
    Entity mEntity;
private:
    World *mWorld;
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

template<typename T>
void EntityHandle::removeComponent()
{
    mWorld->removeComponent<T>(mEntity);
}

#endif // ENTITYHANDLE_H
