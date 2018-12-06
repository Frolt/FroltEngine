#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <unordered_map>
#include <string>
#include "ECS/entity.h"


/**
   @brief The EntityManager class manages all Entities in the gameworld.
   It has two maps for fast lookup by name or ID
 */
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
    /// maps EntityID to the entity name
    std::unordered_map<EntityID, std::string> mIDMap;
    /// maps Entity name to entity instance
    std::unordered_map<std::string, Entity> mEntities;
    /// makes sure each entity gets an unique ID
    static size_t nextID;
};

#endif // ENTITYMANAGER_H
