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
    void setRelativeLocation(const am::Vec3 &location); // done
    void setRelativeRotation(const am::Vec3 &rotation); // done
    void setRelativeScale(const am::Vec3 &scale); // done
    void setWorldLocation(const am::Vec3 &location); // done
    void setWorldRotation(const am::Vec3 &rotation);
    void setWorldScale(const am::Vec3 &location);
    // Adders
    void addRelativeLocation(const am::Vec3 &location); // done
    void addRelativeRotation(const am::Vec3 &rotation); // done
    void addWorldLocation(const am::Vec3 &location); // done
    void addWorldRotation(const am::Vec3 &location);
    // Getters
    am::Vec3 getRelativeLocation(); // done
    am::Vec3 getWorldLocation(); // done

private:
    void addParentLocation(Entity *entity, am::Vec3 &location);
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
