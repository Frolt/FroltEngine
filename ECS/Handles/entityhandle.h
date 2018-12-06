#ifndef ENTITYHANDLE_H
#define ENTITYHANDLE_H

#include "ECS/entity.h"
#include "ECS/Handles/componenthandle.h"
#include "a_math.h"


// Forward declarations
class World;
struct TransformComponent;

/**
   @brief The EntityHandle struct works as a wrapper around an entity.
   It makes it possible to call usefull and common methods from the entityHandle itself.
   Making it more OOP friendly.
 */
struct EntityHandle
{
    EntityHandle() = default;
    EntityHandle(World *world, Entity *entity);

    void destroy();
    /// Creates a new entity that is the child of this entity
    EntityHandle createEntityComponent(const std::string &name);
    /// Makes another entity the child of this entity
    void addEntityComponent(Entity *entity);
    /// Makes another entity the child of this entity
    void addEntityComponent(const EntityHandle &entity);
    template<typename ComponentType>
    void addComponent(const ComponentType &component);
    template<typename ComponentType>
    void removeComponent();
    template<typename ComponentType>
    bool hasComponent();
    /// Overloads the parentheses to return the entity reference
    Entity &operator()();
    /// Overloads the parentheses to return the const entity reference
    const Entity &operator()() const;
    /// Provides implicit casting to an Entity
    operator Entity();
    /// Provides implicit casting to an EntityID
    operator EntityID();

    // Utilities
    //--------------------------------------------------------------------------------------
    // Setters
    void setRelativeLocation(const am::Vec3 &location);
    void setRelativeLocation(float x, float y, float z);
    void setRelativeRotation(const am::Rotator &rotation);
    void setRelativeRotation(float yaw, float pitch, float roll);
    void setRelativeScale(const am::Vec3 &scale);
    void setRelativeScale(float x, float y, float z);
    void setWorldLocation(const am::Vec3 &location);        // TODO
    void setWorldRotation(const am::Rotator &rotation);     // TODO
    void setWorldScale(const am::Vec3 &location);           // TODO
    // Adders
    void addRelativeLocation(const am::Vec3 &location);
    void addRelativeLocation(float x, float y, float z);
    void addRelativeRotation(const am::Rotator &rotation);
    void addRelativeRotation(float yaw, float pitch, float roll);
    void addRelativeScale(const am::Vec3 &scale);
    void addRelativeScale(float x, float y, float z);
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
    /// returns a ModelMatrix that is built from the entity's transform
    am::Mat4 getModelMatrix();
    am::Vec3 getForwardVector();
    am::Vec3 getRightVector();
    am::Vec3 getUpVector();

private:
    /// recursive function that travels up the hierarchy and combines all the model matrices to get world position
    am::Mat4 combineAncestorsTransforms(Entity *entity, const am::Mat4 &prevModelMat = am::Mat4(1));
    /// recursive function that travels up the hierarchy and combines all the ancestors rotations
    am::Vec3 combineAncestorsRotation(Entity *entity, const am::Rotator &prevRotation = am::zero());

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
