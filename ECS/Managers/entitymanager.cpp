#include "entitymanager.h"
#include <QtGlobal>


unsigned long long int EntityManager::nextID = 0;

EntityManager::EntityManager()
{

}

Entity EntityManager::createEntity(const std::string &name)
{
    Entity entity(nextID++, name);
    auto check = mEntities.insert(std::make_pair(entity.mName, entity));
    // Crashes program if key aldready exist
    Q_ASSERT_X(check.second, "ENTITYMANAGER::CREATEENTITY", "KEY ALREADY EXIST");
    return entity;
}

void EntityManager::destroyEntity(const Entity &entity)
{
    mEntities.erase(entity.mName);
}

Entity EntityManager::getEntity(const std::string &name) const
{
    return mEntities.at(name);
}

size_t EntityManager::numOfEntities() const
{
    return mEntities.size();
}
