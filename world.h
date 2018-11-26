#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <typeindex>
#include "ECS/entity.h"

// Forward declarations
class EntityManager;
struct EntityHandle;
class System;
class BaseComponentManager;
struct ComponentMask;
template<typename ComponentType>
struct ComponentHandle;
class Engine;
class EntityFactory;

/**
   @brief The World class is used to provide connection
    between the ECS systems, managers and entity/component handlers.

    If for example an entityHandle instance calls its destroy function, the function will call world
    from its world reference and call the destroyEntity method in the world class.
    This function will then call the destroyEntity function in the EntityManager class instance.
    This is an example on how the world class serve as a crossroad for the ECS system in the engine.
 */
class World
{
public:
    /// Constructor that creates all the component managers, entity manager, and systems
    World(Engine *engine);
    ~World();
    /// Creates a scene with all the entities that the game should start with
    void makeScene(EntityFactory &ef);
    /// Calls beginPlay on all the systems
    void beginPlay();
    /// Calls update on all the systems
    void update(float deltaTime);
    /// Updates the entity list the system cares about after an entity has changed it's component composition
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
    template<typename ComponentType>
    bool hasComponent(EntityID entity);

    // Add and remove component
    template<typename ComponentType>
    void addComponent(EntityID entity, const ComponentType &component);
    template<typename ComponentType>
    void removeComponent(EntityID entity);
    template<typename ComponentType>
    ComponentType *getComponent(EntityID entity);

    // Unpack functions
    /**
       @brief Unpacks all the desired components to an entity. This function uses variadic templates.
       @param entity    The entity you want to unpack
       @param handle    OUT parameter for the component
     */
    template<typename ComponentType>
    void unpack(EntityID entity, ComponentHandle<ComponentType> &handle);
    // Unpack functions
    /**
       @brief Unpacks all the desired components to an entity. This function uses variadic templates.
       @param entity    The entity you want to unpack
       @param handle    OUT parameter for the component
     */
    template<typename ComponentType, typename ...Args>
    void unpack(EntityID entity, ComponentHandle<ComponentType> &handle, ComponentHandle<Args> &...args);

    /// Activate the camera attached to the entity, disables all other cameras since only one camera can be active at a time
    void activateCamera(EntityID entity);

private:
    /// The entity manager stores all entities
    std::unique_ptr<EntityManager> mEntityManager;
    /// A hashcontainer of BaseComponentManagers that can be static casted to the desired manager with typeId()
    std::unordered_map<std::type_index, std::unique_ptr<BaseComponentManager>> mComponentManagers;
    /// A vector that stores all systems
    std::vector<std::unique_ptr<System>> mSystems;
    /// Maps an Entity ID to the belonging ComponentMask
    std::unordered_map<EntityID, ComponentMask> mEntityMasks;
public:
    /// shameful engine reference
    Engine &mEngine;
};


//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

#include "ECS/Handles/componenthandle.h"
#include "ECS/Managers/componentmanager.h"
#include "ECS/component_mask.h"

template<typename ComponentType>
bool World::hasComponent(EntityID entity)
{
    auto *manager = static_cast<ComponentManager<ComponentType> *>(mComponentManagers[typeid (ComponentType)].get());
    return manager->hasComponent(entity);
}

template<typename ComponentType>
void World::unpack(EntityID entity, ComponentHandle<ComponentType> &handle)
{
    handle = ComponentHandle<ComponentType>{this, entity};
}

template<typename ComponentType, typename ...Args>
void World::unpack(EntityID entity, ComponentHandle<ComponentType> &handle, ComponentHandle<Args> &...args)
{
    handle = ComponentHandle<ComponentType>{this, entity};
    unpack<Args...>(entity, args ...);
}

template<typename ComponentType>
void World::addComponent(EntityID entity, const ComponentType &component)
{
    // add component
    auto *manager = static_cast<ComponentManager<ComponentType> *>(mComponentManagers[typeid (ComponentType)].get());
    manager->addComponent(entity, component);

    // update mask
    ComponentMask oldMask = mEntityMasks[entity];
    mEntityMasks[entity].addComponent<ComponentType>();
    updateSystems(entity, oldMask);
}

template<typename ComponentType>
void World::removeComponent(EntityID entity)
{
    auto *manager = static_cast<ComponentManager<ComponentType> *>(mComponentManagers[typeid (ComponentType)].get());
    manager->destroyComponent(entity);

    // update mask
    ComponentMask oldMask = mEntityMasks[entity];
    mEntityMasks[entity].removeCompoent<ComponentType>();
    updateSystems(entity, oldMask);
}

template<typename ComponentType>
ComponentType *World::getComponent(EntityID entity)
{
    auto *manager = static_cast<ComponentManager<ComponentType> *>(mComponentManagers[typeid (ComponentType)].get());
    return manager->getComponent(entity);
}

#endif // WORLD_H
