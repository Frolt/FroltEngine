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
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    transform().mLocation = location;
}

void EntityHandle::setRelativeRotation(const am::Vec3 &rotation)
{
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    transform().mRotation = rotation;
}

void EntityHandle::setRelativeScale(const am::Vec3 &scale)

{
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    transform().mScale = scale;
}

void EntityHandle::setWorldLocation(const am::Vec3 &location)
{
    // TODO
}

void EntityHandle::setWorldRotation(const am::Vec3 &rotation)
{
    // TODO
}

void EntityHandle::setWorldScale(const am::Vec3 &location)
{
    // TODO
}

void EntityHandle::addRelativeLocation(const am::Vec3 &location)
{
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    transform().mLocation += location;
}

void EntityHandle::addRelativeRotation(const am::Vec3 &rotation)
{
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    transform().mRotation += rotation;
}

void EntityHandle::addRelativeScale(const am::Vec3 &scale)
{
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    transform().mScale += scale;
}
void EntityHandle::addWorldLocation(const am::Vec3 &location)
{
    // TODO
}

void EntityHandle::addWorldRotation(const am::Vec3 &location)
{
    // TODO
}

void EntityHandle::addWorldScale(const am::Vec3 &scale)
{
    // TODO
}

am::Vec3 EntityHandle::getRelativeLocation()
{
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    return transform().mLocation;
}

am::Vec3 EntityHandle::getRelativeRotation()
{
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    return transform().mRotation;
}

am::Vec3 EntityHandle::getRelativeScale()
{
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    return transform().mScale;
}

am::Vec3 EntityHandle::getWorldLocation()
{
    auto model = getModelMatrix();
    return {model(0, 3), model(1, 3), model(2, 3)};
}

am::Vec3 EntityHandle::getWorldRotation()
{
    // TODO
    return am::zero();
}

am::Vec3 EntityHandle::getWorldScale()
{
    auto model = getModelMatrix();
    float scaleX = am::Vec(model(0,0), model(1,0), model(2,0)).length();
    float scaleY = am::Vec(model(0,1), model(1,1), model(2,1)).length();
    float scaleZ = am::Vec(model(0,2), model(1,2), model(2,2)).length();
    return am::Vec{scaleX, scaleY, scaleZ};
}

am::Mat4 EntityHandle::getModelMatrix()
{
    am::Mat4 modelMatrix;
    return combineAncestorsTransforms(mEntity, modelMatrix);
}

am::Mat4 EntityHandle::combineAncestorsTransforms(Entity *entity, am::Mat4 &prevModelMat)
{
    ch::Transform transform;
    mWorld->unpack(entity->mID, transform);
    am::Mat4 curModelMat;
    curModelMat.translate(transform().mLocation);
    curModelMat.rotate(transform().mRotation.yaw(), am::up());
    curModelMat.rotate(transform().mRotation.pitch(), am::right());
    curModelMat.rotate(transform().mRotation.roll(), am::forward());
    curModelMat.scale(transform().mScale);

    auto combined = curModelMat * prevModelMat;

    if (entity->mParent)
        return combineAncestorsTransforms(entity->mParent, combined);
    else
        return combined;
}

EntityHandle::operator Entity()
{
    return *mEntity;
}

EntityHandle::operator EntityID()
{
    return mEntity->mID;
}
