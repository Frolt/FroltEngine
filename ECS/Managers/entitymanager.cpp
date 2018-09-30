#include "entitymanager.h"
#include <QtGlobal>


unsigned long long int EntityManager::mNextID = 0;

EntityManager::EntityManager()
{

}

Entity EntityManager::createEntity(const std::string &name)
{
    Entity e(mNextID++, name);
    auto check = mEntities.insert(std::make_pair(e.mName, e));
    // Crashes program if new entity's name is not unique
    Q_ASSERT_X(check.second, "ENTITYMANAGER::CREATEENTITY", "THIS ENTITY ALREADY EXIST");
    return e;
}

void EntityManager::destroyEntity(Entity entity)
{
    mEntities.erase(entity.mName);
}

Entity EntityManager::getEntity(const std::string &name)
{
    return mEntities[name];
}

size_t EntityManager::numOfEntities()
{
    return mEntities.size();
}
