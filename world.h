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
    void updateSystems(EntityID entity, ComponentMask oldMask);

    // Create, destroy and get entity
    EntityHandle createEntity(const std::string &name, Entity *parent = nullptr);
    void destroyEntity(EntityID entity);
    void destroyEntity(const Entity &entity);
    EntityHandle getEntity(EntityID entity);
    EntityHandle getEntity(const std::string &name);
    Entity *getEntityPtr(EntityID entity);
    Entity *getEntityPtr(const std::string &name);
    bool entityExist(EntityID entity);
    bool entityExist(const std::string &name);
    unsigned int getNumberOfEntities();
    template<typename T>
    bool hasComponent(EntityID entity);

    // Add and remove component
    template<typename T>
    void addComponent(EntityID entity, const T &component);
    template<typename T>
    void removeComponent(EntityID entity);
    template<typename T>
    T *getComponent(EntityID entity);

    // Unpack function
    template<typename T>
    void unpack(EntityID entity, ComponentHandle<T> &handle);
    template<typename T, typename ...Args>
    void unpack(EntityID entity, ComponentHandle<T> &handle, ComponentHandle<Args> &...args);

    // Others
    void activateCamera(EntityID entity);

private:
    std::unique_ptr<EntityManager> mEntityManager;
    std::vector<std::unique_ptr<BaseComponentManager>> mComponentManagers;
    std::vector<std::unique_ptr<System>> mSystems;
    std::unordered_map<EntityID, ComponentMask> mEntityMasks;
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
bool World::hasComponent(EntityID entity)
{
    auto *manager = static_cast<ComponentManager<T> *>(mComponentManagers[T::family()].get());
    return manager->hasComponent(entity);
}

template<typename T>
void World::unpack(EntityID entity, ComponentHandle<T> &handle)
{
    handle = ComponentHandle<T>{this, entity};
}

template<typename T, typename ...Args>
void World::unpack(EntityID entity, ComponentHandle<T> &handle, ComponentHandle<Args> &...args)
{
    handle = ComponentHandle<T>{this, entity};
    unpack<Args...>(entity, args ...);
}

template<typename T>
void World::addComponent(EntityID entity, const T &component)
{
    // add component
    auto *manager = static_cast<ComponentManager<T> *>(mComponentManagers[T::family()].get());
    manager->addComponent(entity, component);

    // update mask
    ComponentMask oldMask = mEntityMasks[entity];
    mEntityMasks[entity].addComponent<T>();
    updateSystems(entity, oldMask);
}

template<typename T>
void World::removeComponent(EntityID entity)
{
    auto *manager = static_cast<ComponentManager<T> *>(mComponentManagers[T::family()].get());
    manager->destroyComponent(entity);

    // update mask
    ComponentMask oldMask = mEntityMasks[entity];
    mEntityMasks[entity].removeCompoent<T>();
    updateSystems(entity, oldMask);
}

template<typename T>
T *World::getComponent(EntityID entity)
{
    auto *manager = static_cast<ComponentManager<T> *>(mComponentManagers[T::family()].get());
    return manager->getComponent(entity);
}

#endif // WORLD_H
