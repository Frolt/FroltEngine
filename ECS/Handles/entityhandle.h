#ifndef ENTITYHANDLE_H
#define ENTITYHANDLE_H

#include "ECS/entity.h"
#include "a_math.h"
#include "ECS/Handles/componenthandle.h"

// Forward declarations
class World;
struct TransformComponent;

struct EntityHandle
{
    EntityHandle() = default;
    EntityHandle(World *world, Entity *entity);

    void destroy();
    EntityHandle addEntityComponent(const std::string &name);
    EntityHandle addEntityComponent(Entity *entity);
    template<typename T>
    void addComponent(const T &component);
    template<typename T>
    void removeComponent();
    template<typename T>
    bool hasComponent();
    Entity &operator()();
    const Entity &operator()() const;
    operator Entity();
    operator EntityID();

    // Utilities
    //--------------------------------------------------------------------------------------
    // Relative transformations
    void setRelativeLocation(const am::Vec3 &location);
    am::Vec3 getRelativeLocation();
    void addRelativeLocation(const am::Vec3 &location);
    void setRelativeRotation(const am::Vec3 &location);
    void addRelativeRotation(const am::Vec3 &location);
    void setRelativeScale(const am::Vec3 &location);
    // World transformations
    void setWorldLocation(const am::Vec3 &location);
    am::Vec3 getWorldLocation();
    void addWorldLocation(const am::Vec3 &location);
    void setWorldRotation(const am::Vec3 &location);
    void addWorldRotation(const am::Vec3 &location);
    void setWorldScale(const am::Vec3 &location);

private:
    void addParentLocation(const Entity &entity, am::Vec3 location);
    //--------------------------------------------------------------------------------------

public:
    Entity *mEntity{nullptr};
private:
    World *mWorld{nullptr};
};


//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

#include "world.h"

template<typename T>
void EntityHandle::addComponent(const T &component)
{
    mWorld->addComponent(mEntity->mID, component);
}

template<typename T>
void EntityHandle::removeComponent()
{
    mWorld->removeComponent<T>(mEntity->mID);
}

template<typename T>
bool EntityHandle::hasComponent()
{
    return mWorld->hasComponent<T>(mEntity->mID);
}

#endif // ENTITYHANDLE_H
