#include "entityhandle.h"
#include "ECS/Components/transform_component.h"


EntityHandle::EntityHandle(World *world, Entity *entity)
    : mEntity{entity}, mWorld{world}
{

}

void EntityHandle::destroy()
{
    mWorld->destroyEntity(*mEntity);
}

EntityHandle EntityHandle::createEntityComponent(const std::string &name)
{
    return mWorld->createEntity(name, mEntity);
}

void EntityHandle::addEntityComponent(Entity *entity)
{
    if (entity->mParent)
        entity->mParent->mChild = nullptr;
    mEntity->mChild = entity;
    entity->mParent = mEntity;
}

void EntityHandle::addEntityComponent(const EntityHandle &entity)
{
    auto entityPtr = entity.mEntity;
    if (entityPtr->mParent)
        entityPtr->mParent->mChild = nullptr;
    mEntity->mChild = entityPtr;
    entityPtr->mParent = mEntity;
}

Entity &EntityHandle::operator()()
{
    return *mEntity;
}

const Entity &EntityHandle::operator()() const
{
    return *mEntity;
}

void EntityHandle::setRelativeLocation(const am::Vec3 &location)
{
    // Working
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    transform().mPosition = location;
}

am::Vec3 EntityHandle::getRelativeLocation()
{
    // Working
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    return transform().mPosition;
}

void EntityHandle::addRelativeLocation(const am::Vec3 &location)
{
    // Working
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    transform().mPosition += location;
}

void EntityHandle::setRelativeRotation(const am::Vec3 &rotation)
{
    // Working
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    transform().mRotation += rotation;
}

void EntityHandle::addRelativeRotation(const am::Vec3 &rotation)
{
    // Working
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    transform().mRotation += rotation;
}

void EntityHandle::setRelativeScale(const am::Vec3 &scale)
{
    // Working
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    transform().mScale += scale;
}

void EntityHandle::setWorldLocation(const am::Vec3 &location)
{
    // Working
    am::Vec3 parentWorldLocation;
    if (mEntity->mParent)
        addParentLocation(mEntity->mParent, parentWorldLocation);
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    transform().mPosition = location - parentWorldLocation;
}

am::Vec3 EntityHandle::getWorldLocation()
{
    // Working
    am::Vec3 location;
    addParentLocation(mEntity, location);
    return location;
}

void EntityHandle::addWorldLocation(const am::Vec3 &location)
{
    // Working TESTING
    am::Vec3 parentWorldLocation;
    if (mEntity->mParent)
        addParentLocation(mEntity->mParent, parentWorldLocation);
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);

    auto travelVector = (parentWorldLocation + location) - parentWorldLocation;

    transform().mPosition = parentWorldLocation + location;
}

void EntityHandle::setWorldRotation(const am::Vec3 &rotation)
{

}

void EntityHandle::addWorldRotation(const am::Vec3 &location)
{

}

void EntityHandle::setWorldScale(const am::Vec3 &location)
{

}

void EntityHandle::addParentLocation(Entity *entity, am::Vec3 &location)
{
    if (entity->mParent)
        addParentLocation(entity->mParent, location);
    ch::Transform transform;
    mWorld->unpack(entity->mID, transform);
    location += transform().mPosition;
}

EntityHandle::operator Entity()
{
    return *mEntity;
}

EntityHandle::operator EntityID()
{
    return mEntity->mID;
}
