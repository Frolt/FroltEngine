#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include <string>
#include <map>

// Forward declarations
class EntityManager;
struct EntityHandle;
class System;
class BaseComponentManager;
struct Entity;
struct ComponentMask;
template<typename T>
class ComponentHandle;

class World
{
public:
    World();
    ~World();
    void init();
    void update(float deltaTime);
    void updateSystems(Entity &e, ComponentMask oldMask);

    // Create, destroy and get entity
    EntityHandle createEntity(const std::string &name);
    void destroyEntity(Entity entity);
    EntityHandle getEntity(const std::string &name);

    // Add and remove component
    template<typename T>
    void addComponent(Entity entity, const T &component);
    template<typename T>
    void removeComponent(Entity entity);
    template<typename T>
    T *getComponent(Entity entity);

    // Unpack function
    template<typename T>
    void unpack(Entity entity, ComponentHandle<T> &handle);
    template<typename T, typename ...Args>
    void unpack(Entity entity, ComponentHandle<T> &handle, ComponentHandle<Args> &...args);

private:
    std::vector<std::unique_ptr<System>> mSystems;
    std::vector<std::unique_ptr<BaseComponentManager>> mComponentManagers;
    std::unique_ptr<EntityManager> mEntityManager;
    std::map<Entity, ComponentMask> mEntityMasks;
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

#include "ECS/Handles/componenthandle.h"
#include "ECS/Managers/componentmanager.h"
#include "ECS/component.h"
#include "ECS/entity.h"
#include "ECS/component_mask.h"

template<typename T>
void World::unpack(Entity entity, ComponentHandle<T> &handle)
{
    ComponentManager<T> *manager = static_cast<ComponentManager<T> *>(mComponentManagers[Component<T>::typeID()].get());
    ComponentHandle<T> tmp(this, entity);
    handle = tmp;
}

template<typename T, typename ...Args>
void World::unpack(Entity entity, ComponentHandle<T> &handle, ComponentHandle<Args> &...args)
{
    auto index = Component<T>::typeID();
    ComponentManager<T> *manager = static_cast<ComponentManager<T> *>(mComponentManagers[index].get());
    ComponentHandle<T> tmp(this, entity);
    handle = tmp;
    unpack<Args...>(entity, args ...);
}

template<typename T>
void World::addComponent(Entity entity, const T &component)
{
    // add component
    ComponentManager<T> *manager = static_cast<ComponentManager<T> *>(mComponentManagers[Component<T>::typeID()].get());
    manager->addComponent(entity, component);

    // update mask
    ComponentMask oldMask = mEntityMasks[entity];
    mEntityMasks[entity].addComponent<T>();
    updateSystems(entity, oldMask);
}

template<typename T>
void World::removeComponent(Entity entity)
{
    ComponentManager<T> *manager = static_cast<ComponentManager<T> *>(mComponentManagers[Component<T>::typeID()].get());
    manager->destroy(entity);

    // update mask
    ComponentMask oldMask = mEntityMasks[entity];
    mEntityMasks[entity].removeCompoent<T>();
    updateSystems(entity, oldMask);
}

template<typename T>
T *World::getComponent(Entity entity)
{
    ComponentManager<T> *manager = static_cast<ComponentManager<T> *>(mComponentManagers[Component<T>::typeID()].get());
    return manager->getComponent(entity);
}

#endif // WORLD_H
