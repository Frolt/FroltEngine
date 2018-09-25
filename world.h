#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include "ECS/entity.h"
#include "ECS/componentmanager.h"
#include "ECS/componenthandle.h"

// Forward declarations
class EntityManager;
class System;

class World
{
public:
    World();
    // Begin Play
    void init();
    // Add system
    void addSystem(System *system);
    // Create entity
    void createEntity(const std::string &name);
    // Destroy entity
    void destroyEntity(Entity entity);
    // Add a component
    template<typename T>
    void addComponent(Entity entity, T &&component);
    // Remove a component
    template<typename T>
    void removeComponent(Entity entity);
    // Unpack base function
    template<typename T>
    void unpack(Entity entity, ComponentHandle<T> &handle);
    // Unpack variadic function
    template<typename T, typename ...Args>
    void unpack(Entity entity, ComponentHandle<T> &handle, ComponentHandle<Args> &...args);

private:
    // vector of derived systems
    std::vector<System*> mSystems;
    // vector of derived component managers
    std::vector<BaseComponentManager*> mComponentManagers;
    // Entity manager
    EntityManager *mEntityManager;
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------


template<typename T>
void World::unpack(Entity entity, ComponentHandle<T> &handle)
{
    ComponentManager<T> *manager = static_cast<ComponentManager<T> *>(mComponentManagers[GetComponentFamily<T>()]);
    handle = manager->getComponent(entity);
}

template<typename T, typename ...Args>
void World::unpack(Entity entity, ComponentHandle<T> &handle, ComponentHandle<Args> &...args)
{
    ComponentManager<T> *manager = static_cast<ComponentManager<T> *>(mComponentManagers[GetComponentFamily<T>()]);
    handle = manager->getComponent(entity);
    unpack<Args...>(entity, args ...);
}

template<typename T>
void World::addComponent(Entity entity, T &&component)
{
    ComponentManager<T> *manager = static_cast<ComponentManager<T> *>(mComponentManagers[GetComponentFamily<T>()]);
    manager->addComponent(entity, component);
}

template<typename T>
void World::removeComponent(Entity entity)
{
    ComponentManager<T> *manager = static_cast<ComponentManager<T> *>(mComponentManagers[GetComponentFamily<T>()]);
    manager->destroy(entity);
}

#endif // WORLD_H
