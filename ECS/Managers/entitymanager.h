#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <unordered_map>
#include <map>
#include <string>
#include "ECS/entity.h"

class EntityManager
{
public:
    EntityManager();
    Entity *createEntity(const std::string &name);
    void destroyEntity(EntityID entity);
    void destroyEntity(const Entity &entity);
    Entity *getEntity(const std::string &name);
    Entity *getEntity(EntityID entity);
    bool entityExist(const std::string &name) const;
    bool entityExist(EntityID entity) const;
    size_t numOfEntities() const;

private:
    std::unordered_map<EntityID, std::string> mIDMap;
    std::unordered_map<std::string, Entity> mEntities;
    static size_t nextID;
};

#endif // ENTITYMANAGER_H
