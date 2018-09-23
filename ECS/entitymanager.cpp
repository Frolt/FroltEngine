#include "entitymanager.h"

unsigned int EntityManager::mNextID = 0;

EntityManager::EntityManager()
{

}

Entity EntityManager::createEntity(const std::string &name)
{
    Entity e(mNextID++, name);
    mEntities[name] = e;
    return e;
}

void EntityManager::destroyEntity(Entity entity)
{
    mEntities.erase(entity.mName);
}

Entity EntityManager::getEntity(std::string name)
{
    return mEntities[name];
}
