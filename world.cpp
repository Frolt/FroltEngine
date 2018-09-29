#include "world.h"
#include "ECS/system.h"
#include "ECS/Managers/entitymanager.h"
#include "ECS/Managers/componentmanager.h"
#include "ECS/Handles/entityhandle.h"
#include "ECS/Components/transformcomponent.h"
#include "ECS/Components/movementcomponent.h"

World::World()
{
        mEntityManager = std::make_unique<EntityManager>();
        mComponentManagers.push_back(std::make_unique<ComponentManager<TransformComponent>>());
        mComponentManagers.push_back(std::make_unique<ComponentManager<MovementComponent>>());
        qDebug() << getComponentTypeID<TransformComponent>();
        qDebug() << getComponentTypeID<MovementComponent>();
}

World::~World()
{

}

void World::init()
{
    for (auto &element : mSystems)
        element->beginPlay();
}

void World::update(float deltaTime)
{
    for (auto &element : mSystems)
        element->update(deltaTime);
}

std::unique_ptr<EntityHandle> World::createEntity(const std::string &name)
{
    auto e = mEntityManager->createEntity(name);
    auto eh = std::make_unique<EntityHandle>(this, e);
    return eh;
}

void World::destroyEntity(Entity entity)
{
    mEntityManager->destroyEntity(entity);
}

void World::addSystem(std::unique_ptr<System> system)
{
    mSystems.push_back(std::move(system));
}
