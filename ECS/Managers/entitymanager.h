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
    void destroyEntity(Entity *entity);
    Entity *getEntity(const std::string &name);
    bool entityExist(const std::string &name) const;
    size_t numOfEntities() const;

private:
    std::unordered_map<std::string, Entity> mEntities;
    static unsigned long long int nextID;
};

#endif // ENTITYMANAGER_H
