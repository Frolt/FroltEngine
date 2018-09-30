#include "entityhandle.h"

EntityHandle::EntityHandle()
{

}

EntityHandle::EntityHandle(World *world, Entity entity)
    : mWorld{world}, mEntity{entity}
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
