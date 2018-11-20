#ifndef ENTITYHANDLE_H
#define ENTITYHANDLE_H

#include "ECS/entity.h"
#include "ECS/Handles/componenthandle.h"
#include "a_math.h"

// Forward declarations
class World;
struct TransformComponent;

struct EntityHandle
{
    EntityHandle() = default;
    EntityHandle(World *world, Entity *entity);

    void destroy();
    EntityHandle createEntityComponent(const std::string &name);
    void addEntityComponent(Entity *entity);
    void addEntityComponent(const EntityHandle &entity);
    template<typename ComponentType>
    void addComponent(const ComponentType &component);
    template<typename ComponentType>
    void removeComponent();
    template<typename ComponentType>
    bool hasComponent();
    Entity &operator()();
    const Entity &operator()() const;
    operator Entity();
    operator EntityID();

    // Utilities
    //--------------------------------------------------------------------------------------
    // Setters
    void setRelativeLocation(const am::Vec3 &location);
    void setRelativeRotation(const am::Rotator &rotation);
    void setRelativeScale(const am::Vec3 &scale);
    void setWorldLocation(const am::Vec3 &location);        // TODO
    void setWorldRotation(const am::Rotator &rotation);     // TODO
    void setWorldScale(const am::Vec3 &location);           // TODO
    // Adders
    void addRelativeLocation(const am::Vec3 &location);
    void addRelativeRotation(const am::Rotator &rotation);
    void addRelativeScale(const am::Vec3 &scale);
    void addWorldLocation(const am::Vec3 &location);        // TODO
    void addWorldRotation(const am::Rotator &location);     // TODO
    void addWorldScale(const am::Vec3 &scale);              // TODO
    // Getters
    am::Vec3 getRelativeLocation();
    am::Rotator getRelativeRotation();
    am::Vec3 getRelativeScale();
    am::Vec3 getWorldLocation();
    am::Rotator getWorldRotation();                         // TODO
    am::Vec3 getWorldScale();
    am::Mat4 getModelMatrix();

private:
    am::Mat4 combineAncestorsTransforms(Entity *entity, am::Mat4 &prevModelMat);

public:
    Entity *mEntity{nullptr};
private:
    World *mWorld{nullptr};
};


//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

#include "world.h"

template<typename ComponentType>
void EntityHandle::addComponent(const ComponentType &component)
{
    mWorld->addComponent(mEntity->mID, component);
}

template<typename ComponentType>
void EntityHandle::removeComponent()
{
    mWorld->removeComponent<ComponentType>(mEntity->mID);
}

template<typename ComponentType>
bool EntityHandle::hasComponent()
{
    return mWorld->hasComponent<ComponentType>(mEntity->mID);
}

#endif // ENTITYHANDLE_H
