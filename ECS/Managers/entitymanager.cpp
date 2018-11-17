#include "entitymanager.h"
#include <QtGlobal>
#include <QDebug>


unsigned long long int EntityManager::nextID = 0;

EntityManager::EntityManager()
{

}

Entity *EntityManager::createEntity(const std::string &name)
{
    Entity entity(nextID++, name);
    if (mEntities.find(name) == mEntities.end()) {
        mIDMap[entity.mID] = name;
        mEntities[name] = entity;
        return &mEntities[name];
    } else {
        qDebug() << "ERROR:: Entity already exist";
        return nullptr;
    }
}

void EntityManager::destroyEntity(EntityID entity)
{
    std::string &name = mIDMap[entity];
    mEntities.erase(name);
    mIDMap.erase(entity);
}

void EntityManager::destroyEntity(const Entity &entity)
{
    mIDMap.erase(entity.mID);
    mEntities.erase(entity.mName);
}

Entity *EntityManager::getEntity(const std::string &name)
{
    return &mEntities.at(name);
}

Entity *EntityManager::getEntity(EntityID entity)
{
    std::string &name = mIDMap[entity];
    return &mEntities.at(name);
}

bool EntityManager::entityExist(const std::string &name) const
{
    if (mEntities.find(name) != mEntities.end())
        return true;
    return false;
}

bool EntityManager::entityExist(EntityID entity) const
{
    if (mIDMap.find(entity) != mIDMap.end())
        return true;
    return false;
}

size_t EntityManager::numOfEntities() const
{
    return mEntities.size();
}
