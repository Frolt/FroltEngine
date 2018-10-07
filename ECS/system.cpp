#include "system.h"


System::~System()
{

}

void System::beginPlay()
{

}

void System::update(float)
{

}

void System::setWorld(World *world)
{
    mWorld = world;
}

void System::registerEntity(const Entity &entity)
{
    mRegisteredEntities.push_back(entity);
}

void System::deRegisterEntity(const Entity &entity)
{
    for (auto it = mRegisteredEntities.begin(); it != mRegisteredEntities.end(); ++it) {
      Entity e = *it;
      if (e == entity) {
        mRegisteredEntities.erase(it);
        return;
      }
    }
}
