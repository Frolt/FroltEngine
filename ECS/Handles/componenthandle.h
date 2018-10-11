#ifndef COMPONENTHANDLE_H
#define COMPONENTHANDLE_H

#include "ECS/entity.h"

// Forward declarations
template<typename T>
class ComponentManager;
class World;

template<typename T>
struct ComponentHandle
{
    ComponentHandle() = default;
    ComponentHandle(World *world, const Entity &entity);
    void destroy();
    T &operator()();
    const T &operator()() const;
    operator T&();

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
ComponentHandle<T>::ComponentHandle(World *world, const Entity &entity)
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

template<typename T>
const T &ComponentHandle<T>::operator()() const
{
    return *mComponent;
}

template<typename T>
ComponentHandle<T>::operator T&()
{
    return *mComponent;
}

#endif // COMPONENTHANDLE_H
