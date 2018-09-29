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
    Entity getEntity(std::string name);

private:
    std::map<std::string, Entity> mEntities;
    static unsigned int mNextID;
};

#endif // ENTITYMANAGER_H
