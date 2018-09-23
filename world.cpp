#include "world.h"
#include "ECS/system.h"
#include "ECS/entitymanager.h"
#include "ECS/entityhandle.h"

World::World()
{

}

void World::init()
{
    for (auto &element : mSystems)
        element->init();
}

void World::createEntity(const std::string &name)
{
    mEntityManager->createEntity(name);
}

void World::destroyEntity(Entity entity)
{
    mEntityManager->destroyEntity(entity);
}

void World::addSystem(System *system)
{
    mSystems.push_back(system);
}
