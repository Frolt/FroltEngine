#ifndef COMPONENTHANDLE_H
#define COMPONENTHANDLE_H

#include "ECS/entity.h"

// Forward declarations
template<typename T>
class ComponentManager;

template<typename T>
class ComponentHandle
{
public:
    ComponentHandle();
    ComponentHandle(Entity entity, ComponentManager<T> *manager);
    void destroy();
    T &operator()();

public:
    T *mComponent{nullptr};

private:
    Entity mOwner;
    ComponentManager<T> *mManager{nullptr};
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

#include "ECS/Managers/componentmanager.h"

template<typename T>
ComponentHandle<T>::ComponentHandle()
{

}

template<typename T>
ComponentHandle<T>::ComponentHandle(Entity entity, ComponentManager<T> *manager)
    : mOwner{entity}, mManager{manager}
{
    mComponent = manager->getComponent(entity);
}

template<typename T>
void ComponentHandle<T>::destroy()
{
    // TODO need to update systems
    mManager->destroy(mOwner);
}

template<typename T>
T &ComponentHandle<T>::operator()()
{
    return *mComponent;
}

#endif // COMPONENTHANDLE_H
