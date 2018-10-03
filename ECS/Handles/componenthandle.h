#ifndef COMPONENTHANDLE_H
#define COMPONENTHANDLE_H

#include "ECS/entity.h"

// Forward declarations
template<typename T>
class ComponentManager;
class World;

template<typename T>
class ComponentHandle
{
public:
    ComponentHandle();
    ComponentHandle(World *world, Entity entity);
    void destroy();
    T &operator()();

public:
    T *mComponent{nullptr};

private:
    World *mWorld;
    Entity mOwner;
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

#include "ECS/Managers/componentmanager.h"
#include "world.h"

template<typename T>
ComponentHandle<T>::ComponentHandle()
{

}

template<typename T>
ComponentHandle<T>::ComponentHandle(World *world, Entity entity)
    : mWorld{world}, mOwner{entity}
{
    mComponent = mWorld->getComponent<T>(entity);
}

template<typename T>
void ComponentHandle<T>::destroy()
{
    mWorld->removeComponent<T>(mOwner);
}

template<typename T>
T &ComponentHandle<T>::operator()()
{
    return *mComponent;
}

#endif // COMPONENTHANDLE_H
