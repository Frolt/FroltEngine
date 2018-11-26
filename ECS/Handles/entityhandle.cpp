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

void EntityHandle::setRelativeLocation(float x, float y, float z)
{
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    transform().mLocation = am::Vec3(x,y,z);
}

void EntityHandle::setRelativeRotation(const am::Rotator &rotation)
{
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    transform().mRotation = rotation;
}

void EntityHandle::setRelativeRotation(float yaw, float pitch, float roll)
{
    am::Rotator rotation;
    rotation.yaw = yaw;
    rotation.pitch = pitch;
    rotation.roll = roll;
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

void EntityHandle::setRelativeScale(float x, float y, float z)
{
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    transform().mScale = am::Vec3(x,y,z);
}

void EntityHandle::addRelativeLocation(const am::Vec3 &location)
{
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    transform().mLocation += location;
}

void EntityHandle::addRelativeLocation(float x, float y, float z)
{
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    transform().mLocation += am::Vec3(x,y,z);
}

void EntityHandle::addRelativeRotation(const am::Rotator &rotation)
{
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    transform().mRotation += rotation;
}

void EntityHandle::addRelativeRotation(float yaw, float pitch, float roll)
{
    am::Rotator rotation;
    rotation.yaw = yaw;
    rotation.pitch = pitch;
    rotation.roll = roll;
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

void EntityHandle::addRelativeScale(float x, float y, float z)
{
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    transform().mScale += am::Vec3(x,y,z);
}

am::Vec3 EntityHandle::getRelativeLocation()
{
    ch::Transform transform;
    mWorld->unpack(mEntity->mID, transform);
    return transform().mLocation;
}

am::Rotator EntityHandle::getRelativeRotation()
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
    return combineAncestorsTransforms(mEntity);
}

am::Vec3 EntityHandle::getForwardVector()
{
    am::Vec3 worldRotation = combineAncestorsRotation(mEntity);
    am::Vec front;
    front.x = cos(am::toRadians(worldRotation.yaw)) * cos(am::toRadians(worldRotation.pitch));
    front.y = sin(am::toRadians(worldRotation.pitch));
    front.z = -sin(am::toRadians(worldRotation.yaw)) * cos(am::toRadians(worldRotation.pitch));
    return am::normalize(front);
}

am::Vec3 EntityHandle::getRightVector()
{
    am::Vec3 worldRotation = combineAncestorsRotation(mEntity);
    am::Vec front;
    front.x = cos(am::toRadians(worldRotation.yaw)) * cos(am::toRadians(worldRotation.pitch));
    front.y = sin(am::toRadians(worldRotation.pitch));
    front.z = -sin(am::toRadians(worldRotation.yaw)) * cos(am::toRadians(worldRotation.pitch));
    front.normalize();
    return am::normalize(am::cross(front, am::up()));
}

am::Vec3 EntityHandle::getUpVector()
{
    am::Vec3 worldRotation = combineAncestorsRotation(mEntity);
    am::Vec front;
    front.x = cos(am::toRadians(worldRotation.yaw)) * cos(am::toRadians(worldRotation.pitch));
    front.y = sin(am::toRadians(worldRotation.pitch));
    front.z = -sin(am::toRadians(worldRotation.yaw)) * cos(am::toRadians(worldRotation.pitch));
    front.normalize();
    am::Vec right = am::normalize(am::cross(front, am::up()));
    return -am::normalize(am::cross(front, right));
}

am::Mat4 EntityHandle::combineAncestorsTransforms(Entity *entity, const am::Mat4 &prevModelMat)
{
    ch::Transform transform;
    mWorld->unpack(entity->mID, transform);
    am::Mat4 curModelMat;
    curModelMat.translate(transform().mLocation);
    curModelMat.rotate(transform().mRotation.yaw, am::up());
    curModelMat.rotate(transform().mRotation.pitch, am::right());
    curModelMat.rotate(transform().mRotation.roll, am::forward());
    curModelMat.scale(transform().mScale);

    auto combined = curModelMat * prevModelMat;

    if (entity->mParent)
        return combineAncestorsTransforms(entity->mParent, combined);
    else
        return combined;
}

am::Vec3 EntityHandle::combineAncestorsRotation(Entity *entity, const am::Rotator &prevRotation)
{
    ch::Transform transform;
    mWorld->unpack(entity->mID, transform);
    auto combined = prevRotation + transform().mRotation;

    if (entity->mParent)
        return combineAncestorsRotation(entity->mParent, combined);
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
