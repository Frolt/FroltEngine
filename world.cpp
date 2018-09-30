#include "world.h"
#include "ECS/system.h"
#include "ECS/Managers/entitymanager.h"
#include "ECS/Managers/componentmanager.h"
#include "ECS/Handles/entityhandle.h"
#include "ECS/Components/transformcomponent.h"
#include "ECS/Components/movementcomponent.h"
#include "ECS/componentmask.h"
#include "ECS/Systems/movementsystem.h"

World::World()
{
    // Create entity manager
    mEntityManager = std::make_unique<EntityManager>();
    // Create component managers
    mComponentManagers.push_back(std::make_unique<ComponentManager<TransformComponent>>());
    mComponentManagers.push_back(std::make_unique<ComponentManager<MovementComponent>>());
    // Create systems
    mSystems.push_back(std::make_unique<MovementSystem>());
    // Set world pointer for all systems
    for (auto &sys : mSystems)
        sys->setWorld(this);
}

World::~World()
{

}

void World::init()
{
    for (auto &sys : mSystems)
        sys->beginPlay();
}

void World::update(float deltaTime)
{
    for (auto &sys : mSystems)
        sys->update(deltaTime);
}

void World::updateSystems(Entity &e, ComponentMask oldMask)
{
    ComponentMask newMask = mEntityMasks[e];

    for (auto &sys : mSystems) {
      if (newMask.isNewMatch(oldMask, sys->mSystemMask)) {
        sys->registerEntity(e);
      } else if (newMask.noLongerMatched(oldMask, sys->mSystemMask)) {
        sys->deRegisterEntity(e);
      }
    }
}

EntityHandle World::createEntity(const std::string &name)
{
    auto e = mEntityManager->createEntity(name);
    return EntityHandle(this, e);
}

void World::destroyEntity(Entity entity)
{
    mEntityManager->destroyEntity(entity);
}

EntityHandle World::getEntity(const std::string &name)
{
    auto e = mEntityManager->getEntity(name);
    return EntityHandle(this, e);
}
