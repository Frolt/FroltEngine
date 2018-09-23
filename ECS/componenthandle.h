#ifndef COMPONENTHANDLE_H
#define COMPONENTHANDLE_H

#include "entity.h"
#include "wrappers.h"

// Forward declarations
template<typename T>
class ComponentManager;

template<typename T>
class ComponentHandle
{
public:
    ComponentHandle();
    ComponentHandle(ComponentManager<T> *manager, ComponentInstance instance, Entity entity);
    void destroy();

public:
    Entity mOwner;
    T *mComponent{nullptr};
    ComponentManager<T> *mManager{nullptr};
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

template<typename T>
ComponentHandle<T>::ComponentHandle()
{

}

template<typename T>
ComponentHandle<T>::ComponentHandle(ComponentManager<T> *manager, ComponentInstance instance, Entity entity)
{
    mOwner = entity;
    mComponent = manager->getComponent(entity);
    mManager = manager;
}

template<typename T>
void ComponentHandle<T>::destroy()
{
    mManager->destroy(mOwner);
}

#endif // COMPONENTHANDLE_H
