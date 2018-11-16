#include "entityhandle.h"
#include "ECS/Components/transform_component.h"


EntityHandle::EntityHandle(World *world, Entity *entity)
    : mEntity{entity}, mWorld{world}
{

}

void EntityHandle::destroy()
{
    mWorld->destroyEntity(mEntity);
}

EntityHandle EntityHandle::addEntityComponent(const std::string &name)
{
    return mWorld->createEntity(name, mEntity);
}

EntityHandle EntityHandle::addEntityComponent(Entity &entity)
{
    // TODO fix
//    mEntity.mChild = mWorld->getEntity(entity.mName);
    return{};
}

Entity *EntityHandle::operator()()
{
    return mEntity;
}

const Entity *EntityHandle::operator()() const
{
    return mEntity;
}

void EntityHandle::setRelativeLocation(const am::Vec3 &location)
{
    // TODO fix
    ch::Transform transform;
    mWorld->unpack(mEntity, transform);
    transform().mPosition = location;
}

am::Vec3 EntityHandle::getRelativeLocation()
{
    ch::Transform transform;
    mWorld->unpack(mEntity, transform);
    return transform().mPosition;
}

void EntityHandle::addRelativeLocation(const am::Vec3 &location)
{
    // TODO fix
    ch::Transform transform;
    mWorld->unpack(mEntity, transform);
    transform().mPosition += location;
}

void EntityHandle::setRelativeRotation(const am::Vec3 &location)
{

}

void EntityHandle::addRelativeRotation(const am::Vec3 &location)
{

}

void EntityHandle::setRelativeScale(const am::Vec3 &location)
{

}

void EntityHandle::setWorldLocation(const am::Vec3 &location)
{
    am::Vec3 worldLocation;
    ch::Transform transform;
    mWorld->unpack(mEntity, transform);
    ch::Transform parentTransform;
    mWorld->unpack(mEntity->mParent, parentTransform);
    transform().mPosition += location - parentTransform().mPosition;
}

am::Vec3 EntityHandle::getWorldLocation()
{
    am::Vec3 location;
    addParentLocation(mEntity, location);
    return location;
}

void EntityHandle::addWorldLocation(const am::Vec3 &location)
{

}

void EntityHandle::setWorldRotation(const am::Vec3 &location)
{

}

void EntityHandle::addWorldRotation(const am::Vec3 &location)
{

}

void EntityHandle::setWorldScale(const am::Vec3 &location)
{

}

void EntityHandle::addParentLocation(Entity *entity, am::Vec3 location)
{
    if (entity->mParent)
        addParentLocation(entity->mParent, location);
    ch::Transform transform;
    mWorld->unpack(entity, transform);
    location += transform().mPosition;
}

EntityHandle::operator Entity()
{
    return *mEntity;
}
