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
    EntityHandle createEntityComponent(const std::string &name);
    void addEntityComponent(Entity *entity);
    void addEntityComponent(const EntityHandle &entity);
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
    // Setters
    void setRelativeLocation(const am::Vec3 &location);
    void setRelativeRotation(const am::Vec3 &rotation);
    void setRelativeScale(const am::Vec3 &scale);
    void setWorldLocation(const am::Vec3 &location);    // TODO
    void setWorldRotation(const am::Vec3 &rotation);    // TODO
    void setWorldScale(const am::Vec3 &location);       // TODO
    // Adders
    void addRelativeLocation(const am::Vec3 &location);
    void addRelativeRotation(const am::Vec3 &rotation);
    void addRelativeScale(const am::Vec3 &scale);
    void addWorldLocation(const am::Vec3 &location);    // TODO
    void addWorldRotation(const am::Vec3 &location);    // TODO
    void addWorldScale(const am::Vec3 &scale);          // TODO
    // Getters
    am::Vec3 getRelativeLocation();
    am::Vec3 getRelativeRotation();
    am::Vec3 getRelativeScale();
    am::Vec3 getWorldLocation();
    am::Vec3 getWorldRotation();        // TODO
    am::Vec3 getWorldScale();

    am::Mat4 getModelMatrix();

private:
    am::Mat4 combineAncestorsTransforms(Entity *entity, am::Mat4 &prevModelMat);
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
