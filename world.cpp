#include "world.h"
#include "ECS/system.h"
#include "ECS/component_mask.h"
#include "ECS/Managers/entitymanager.h"
#include "ECS/Managers/componentmanager.h"
#include "ECS/Handles/entityhandle.h"
#include "ECS/Components/transform_component.h"
#include "ECS/Components/movement_component.h"
#include "ECS/Components/mesh_component.h"
#include "ECS/Components/material_component.h"
#include "ECS/Components/directionallight_component.h"
#include "ECS/Components/pointlight_component.h"
#include "ECS/Components/spotlight_component.h"
#include "ECS/Components/input_component.h"
#include "ECS/Components/camera_component.h"
#include "ECS/Components/free_camera_component.h"
#include "ECS/Components/terrain_component.h"
#include "ECS/Components/model_component.h"
#include "ECS/Components/physics_component.h"
#include "ECS/Components/bspline_component.h"
#include "ECS/Components/trophy_component.h"
#include "ECS/Components/collision_component.h"
#include "ECS/Systems/movementsystem.h"
#include "ECS/Systems/rendersystem.h"
#include "ECS/Systems/directionallightsystem.h"
#include "ECS/Systems/pointlightsystem.h"
#include "ECS/Systems/spotlightsystem.h"
#include "ECS/Systems/playersystem.h"
#include "ECS/Systems/freecamerasystem.h"
#include "ECS/Systems/modelrendersystem.h"
#include "ECS/Systems/physicssystem.h"
#include "ECS/Systems/aisystem.h"
#include "ECS/Systems/collisionsystem.h"
#include "ECS/Systems/combatsystem.h"
#include "engine.h"

World::World(Engine *engine)
    : mEngine{*engine}
{
    mComponentManagers.resize(64);
    // Create entity manager
    mEntityManager = std::make_unique<EntityManager>();
    // Create component managers
    mComponentManagers[TransformComponent::family()] = std::make_unique<ComponentManager<TransformComponent>>(100000);
    mComponentManagers[MovementComponent::family()] = std::make_unique<ComponentManager<MovementComponent>>(100000);
    mComponentManagers[MeshComponent::family()] = std::make_unique<ComponentManager<MeshComponent>>(100000);
    mComponentManagers[MaterialComponent::family()] = std::make_unique<ComponentManager<MaterialComponent>>(100000);
    mComponentManagers[DirectionalLightComponent::family()] = std::make_unique<ComponentManager<DirectionalLightComponent>>(100);
    mComponentManagers[PointLightComponent::family()] = std::make_unique<ComponentManager<PointLightComponent>>(100);
    mComponentManagers[SpotlightComponent::family()] = std::make_unique<ComponentManager<SpotlightComponent>>(100);
    mComponentManagers[InputComponent::family()] = std::make_unique<ComponentManager<InputComponent>>(100000);
    mComponentManagers[CameraComponent::family()] = std::make_unique<ComponentManager<CameraComponent>>(10);
    mComponentManagers[FreeCameraComponent::family()] = std::make_unique<ComponentManager<FreeCameraComponent>>(10);
    mComponentManagers[TerrainComponent::family()] = std::make_unique<ComponentManager<TerrainComponent>>(100);
    mComponentManagers[ModelComponent::family()] = std::make_unique<ComponentManager<ModelComponent>>(100000);
    mComponentManagers[PhysicsComponent::family()] = std::make_unique<ComponentManager<PhysicsComponent>>(100000);
    mComponentManagers[BSplineComponent::family()] = std::make_unique<ComponentManager<BSplineComponent>>(100000);
    mComponentManagers[TrophyComponent::family()] = std::make_unique<ComponentManager<TrophyComponent>>(100000);
    mComponentManagers[CollisionComponent::family()] = std::make_unique<ComponentManager<CollisionComponent>>(100000);
    // Create systems
    mSystems.push_back(std::make_unique<MovementSystem>());
    mSystems.push_back(std::make_unique<DirectionalLightSystem>());
    mSystems.push_back(std::make_unique<PointLightSystem>());
    mSystems.push_back(std::make_unique<SpotlightSystem>());
    mSystems.push_back(std::make_unique<playerSystem>());
    mSystems.push_back(std::make_unique<FreeCameraSystem>());
    mSystems.push_back(std::make_unique<modelRenderSystem>());
    mSystems.push_back(std::make_unique<PhysicsSystem>());
    mSystems.push_back(std::make_unique<AISystem>());
    mSystems.push_back(std::make_unique<CollisionSystem>());
    mSystems.push_back(std::make_unique<CombatSystem>());
    mSystems.push_back(std::make_unique<RenderSystem>());
    // Set world and eventbus pointer for all systems
    for (auto &sys : mSystems) {
        sys->setWorld(this);
        sys->setEventBus(mEngine.mEventBus.get());
    }
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

void World::updateSystems(Entity *entity, ComponentMask oldMask)
{
    ComponentMask newMask = mEntityMasks[*entity];

    for (auto &sys : mSystems) {
      if (newMask.isNewMatch(oldMask, sys->mSystemMask)) {
        sys->registerEntity(entity);
      } else if (newMask.noLongerMatched(oldMask, sys->mSystemMask)) {
        sys->deRegisterEntity(entity);
      }
    }
}

EntityHandle World::createEntity(const std::string &name, Entity *parent)
{
    auto *entity = mEntityManager->createEntity(name);
    mEntityMasks.insert(std::make_pair(*entity, ComponentMask()));
    if (parent) {
        parent->mChild = entity;
        entity->mParent = parent;
    }
    return EntityHandle(this, entity);
}

void World::destroyEntity(Entity *entity)
{
    // Update the parent/child relationship
    if (entity->mParent)
        entity->mParent->mChild = nullptr;
    if (entity->mChild)
        destroyEntity(entity->mChild);

    // Destroy all components belonging to entity
    for (auto &manager : mComponentManagers) {
        if (!manager)
            break;
        manager->destroyComponent(entity);
    }
    // Update mask
    ComponentMask oldMask = mEntityMasks[*entity];
    mEntityMasks[*entity].reset();
    updateSystems(entity, oldMask);
    // Destroy mask and entity
    mEntityMasks.erase(*entity);
    mEntityManager->destroyEntity(entity);
}

EntityHandle World::getEntity(const std::string &name)
{
    auto *entity = mEntityManager->getEntity(name);
    return EntityHandle(this, entity);
}

Entity *World::getEntityPtr(const std::string &name)
{
    return mEntityManager->getEntity(name);
}

bool World::entityExist(const std::string &name)
{
    return mEntityManager->entityExist(name);
}
