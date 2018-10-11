#include "entityhandle.h"


EntityHandle::EntityHandle(World *world, const Entity &entity)
    : mEntity{entity}, mWorld{world}
{

}

void EntityHandle::destroy()
{
    mWorld->destroyEntity(mEntity);
}

Entity &EntityHandle::operator()()
{
    return mEntity;
}

const Entity &EntityHandle::operator()() const
{
    return mEntity;
}

EntityHandle::operator Entity()
{
    return mEntity;
}
