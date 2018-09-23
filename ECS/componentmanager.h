#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <map>
#include <array>
#include <functional>
#include "entity.h"
#include "componenthandle.h"
#include "wrappers.h"
#include "basecomponentmanager.h"

// Generic component manager
template <typename T>
class ComponentManager : public BaseComponentManager
{
public:
    ComponentInstance addComponent(Entity entity, T &component);
    T* getComponent(Entity entity);
    void destroy(Entity entity);
    void iterateAll(std::function<void(T component)> lambda);
    ComponentHandle<T> getHandle(Entity entity);

private:
    std::map<Entity, ComponentInstance> mEntityMap;
    ComponentData<T> mComponentData;
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

template<typename T>
ComponentInstance ComponentManager<T>::addComponent(Entity entity, T &component)
{
    ComponentInstance newInstance(mComponentData.size);
    mComponentData.data[newInstance] = component;
    mEntityMap[entity] = newInstance;
    mComponentData.size++;
    return newInstance;
    //    mComponentData.data[mComponentData.size++] = component;
}

template<typename T>
T *ComponentManager<T>::getComponent(Entity entity)
{
    ComponentInstance instance = mEntityMap[entity];
    return mComponentData.data[instance.mIndex];
}

template<typename T>
void ComponentManager<T>::destroy(Entity entity)
{
    ComponentInstance instance = mEntityMap[entity];
    mComponentData.data[instance] = mComponentData.data[mComponentData.size - 1];
    mEntityMap.erase(entity);
    mComponentData.size--;

}

template<typename T>
void ComponentManager<T>::iterateAll(std::function<void(T component)> lambda)
{
    for(unsigned int i = 1; i < mComponentData.size; i++)
      lambda(mComponentData.data[i]);
}

template<typename T>
ComponentHandle<T> ComponentManager<T>::getHandle(Entity entity)
{
      ComponentInstance inst = mEntityMap[entity];
      return ComponentHandle<T>(this, inst, entity);
}


#endif // COMPONENTMANAGER_H
