#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <map>
#include "ECS/entity.h"

// Forward declarations
class EntityManager;
struct EntityHandle;
class System;
class BaseComponentManager;
struct ComponentMask;
template<typename T>
struct ComponentHandle;
class Engine;

class World
{
public:
    World(Engine *engine);
    ~World();
    void init();
    void update(float deltaTime);
    void updateSystems(Entity *entity, ComponentMask oldMask);

    // Create, destroy and get entity
    EntityHandle createEntity(const std::string &name, Entity *parent = nullptr);
    void destroyEntity(Entity *entity);
    EntityHandle getEntity(const std::string &name);
    Entity *getEntityPtr(const std::string &name);
    bool entityExist(const std::string &name);
    template<typename T>
    bool hasComponent(Entity *entity);

    // Add and remove component
    template<typename T>
    void addComponent(Entity *entity, const T &component);
    template<typename T>
    void removeComponent(Entity *entity);
    template<typename T>
    T *getComponent(Entity *entity);

    // TODO snakk med ole, støtter ikke user defined klasser, må recompile
    // Unpack function
    template<typename T>
    void unpack(Entity *entity, ComponentHandle<T> &handle);
    template<typename T, typename ...Args>
    void unpack(Entity *entity, ComponentHandle<T> &handle, ComponentHandle<Args> &...args);

private:
    std::unique_ptr<EntityManager> mEntityManager;
    std::vector<std::unique_ptr<BaseComponentManager>> mComponentManagers;
    std::vector<std::unique_ptr<System>> mSystems;
    // TODO snakk med Ole, hash tregere enn reblack tree?
    std::unordered_map<Entity, ComponentMask> mEntityMasks;
    // TODO snakk med Ole, engine ref i world
public:
    Engine &mEngine;
};


//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

#include "ECS/Handles/componenthandle.h"
#include "ECS/Managers/componentmanager.h"
#include "ECS/component.h"
#include "ECS/component_mask.h"

template<typename T>
bool World::hasComponent(Entity *entity)
{
    auto *manager = static_cast<ComponentManager<T> *>(mComponentManagers[T::family()].get());
    return manager->hasComponent(entity);
}

template<typename T>
void World::unpack(Entity *entity, ComponentHandle<T> &handle)
{
    handle = ComponentHandle<T>{this, entity};
}

template<typename T, typename ...Args>
void World::unpack(Entity *entity, ComponentHandle<T> &handle, ComponentHandle<Args> &...args)
{
    handle = ComponentHandle<T>{this, entity};
    unpack<Args...>(entity, args ...);
}

template<typename T>
void World::addComponent(Entity *entity, const T &component)
{
    // add component
    auto *manager = static_cast<ComponentManager<T> *>(mComponentManagers[T::family()].get());
    manager->addComponent(entity, component);

    // update mask
    ComponentMask oldMask = mEntityMasks[*entity];
    mEntityMasks[*entity].addComponent<T>();
    updateSystems(entity, oldMask);
}

template<typename T>
void World::removeComponent(Entity *entity)
{
    auto *manager = static_cast<ComponentManager<T> *>(mComponentManagers[T::family()].get());
    manager->destroyComponent(entity);

    // update mask
    ComponentMask oldMask = mEntityMasks[*entity];
    mEntityMasks[*entity].removeCompoent<T>();
    updateSystems(entity, oldMask);
}

template<typename T>
T *World::getComponent(Entity *entity)
{
    auto *manager = static_cast<ComponentManager<T> *>(mComponentManagers[T::family()].get());
    return manager->getComponent(entity);
}

#endif // WORLD_H
