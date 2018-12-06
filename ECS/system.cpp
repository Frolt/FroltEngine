#include "system.h"


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

void System::setEventHandler(EventHandler *eventHandler)
{
    mEventHandler = eventHandler;
}

void System::registerEntity(EntityID entity)
{
    mRegisteredEntities.push_back(entity);
}

void System::deRegisterEntity(EntityID entity)
{
    for (auto it = mRegisteredEntities.begin(); it != mRegisteredEntities.end(); ++it) {
        if (*it == entity) {
            mRegisteredEntities.erase(it);
            return;
        }
    }
}
