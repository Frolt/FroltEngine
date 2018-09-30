#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <map>
#include <string>
#include "ECS/entity.h"

class EntityManager
{
public:
    EntityManager();
    Entity createEntity(const std::string &name);
    void destroyEntity(Entity entity);
    Entity getEntity(const std::string &name);
    size_t numOfEntities();

private:
    std::map<std::string, Entity> mEntities;
    static unsigned long long int mNextID;
};

#endif // ENTITYMANAGER_H
