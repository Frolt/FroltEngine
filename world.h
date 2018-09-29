#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include <string>
#include "ECS/entity.h"

// Forward declarations
class EntityManager;
struct EntityHandle;
class System;
class BaseComponentManager;
template<typename T>
class ComponentHandle;

class World
{
public:
    World();
    ~World();
    void init();
    void update(float deltaTime);
    void addSystem(std::unique_ptr<System> system);
    std::unique_ptr<EntityHandle> createEntity(const std::string &name);
    void destroyEntity(Entity entity);

    template<typename T>
    void addComponent(Entity entity, const T &component);
    template<typename T>
    void removeComponent(Entity entity);

    // UNPACKS A GIVEN ENTITTY'S COMPONENTS
    // Unpack() base template function
    template<typename T>
    void unpack(Entity entity, ComponentHandle<T> &handle);
    // Unpack() variadic template function
    template<typename T, typename ...Args>
    void unpack(Entity entity, ComponentHandle<T> &handle, ComponentHandle<Args> &...args);

private:
    std::vector<std::unique_ptr<System>> mSystems;
    std::vector<std::unique_ptr<BaseComponentManager>> mComponentManagers;
    std::unique_ptr<EntityManager> mEntityManager;
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

#include "ECS/Handles/componenthandle.h"
#include "ECS/Managers/componentmanager.h"
#include "ECS/component.h"

template<typename T>
void World::unpack(Entity entity, ComponentHandle<T> &handle)
{
    ComponentManager<T> *manager = static_cast<ComponentManager<T> *>(mComponentManagers[getComponentTypeID<T>()].get());
    ComponentHandle<T> tmp(entity, manager);
    handle = tmp;
}

template<typename T, typename ...Args>
void World::unpack(Entity entity, ComponentHandle<T> &handle, ComponentHandle<Args> &...args)
{
    ComponentManager<T> *manager = static_cast<ComponentManager<T> *>(mComponentManagers[getComponentTypeID<T>()].get());
    ComponentHandle<T> tmp(entity, manager);
    handle = tmp;
    unpack<Args...>(entity, args ...);
}

template<typename T>
void World::addComponent(Entity entity, const T &component)
{
    ComponentManager<T> *manager = static_cast<ComponentManager<T> *>(mComponentManagers[getComponentTypeID<T>()].get());
    manager->addComponent(entity, component);
}

template<typename T>
void World::removeComponent(Entity entity)
{
    ComponentManager<T> *manager = static_cast<ComponentManager<T> *>(mComponentManagers[getComponentTypeID<T>()].get());
    manager->destroy(entity);
}

#endif // WORLD_H
