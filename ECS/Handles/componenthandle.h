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

public:
    // TODO overload . operator to return mComponent pointer
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
    mManager->destroy(mOwner);
}

#endif // COMPONENTHANDLE_H
