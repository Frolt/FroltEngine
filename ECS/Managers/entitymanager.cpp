#include "entitymanager.h"
#include <QtGlobal>


unsigned long long int EntityManager::nextID = 0;

EntityManager::EntityManager()
{

}

Entity *EntityManager::createEntity(const std::string &name)
{
    Entity entity(nextID++, name);
    auto check = mEntities.insert(std::make_pair(entity.mName, entity));
    // Crashes program if key aldready exist
    Q_ASSERT_X(check.second, "ENTITYMANAGER::CREATEENTITY", "KEY ALREADY EXIST");
    return &mEntities[entity.mName];
}

void EntityManager::destroyEntity(const std::string &name)
{
    mEntities.erase(name);
}

Entity *EntityManager::getEntity(const std::string &name)
{
    return &mEntities.at(name);
}

bool EntityManager::entityExist(const std::string &name) const
{
    if (mEntities.find(name) != mEntities.end())
        return true;
    return false;
}

size_t EntityManager::numOfEntities() const
{
    return mEntities.size();
}
