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
#include "ECS/Components/inputcomponent.h"
#include "ECS/Components/cameracomponent.h"
#include "ECS/Components/freecameracomponent.h"
#include "ECS/Systems/movementsystem.h"
#include "ECS/Systems/rendersystem.h"
#include "ECS/Systems/directionallightsystem.h"
#include "ECS/Systems/pointlightsystem.h"
#include "ECS/Systems/spotlightsystem.h"
#include "ECS/Systems/playersystem.h"
#include "ECS/Systems/freecamerasystem.h"

World::World()
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
//    qDebug() << "Transform \tindex[0] = " << TransformComponent::family();
//    qDebug() << "Movement \t\tindex[0] = " << MovementComponent::family();
//    qDebug() << "Mesh \t\tindex[0] = " << MeshComponent::family();
//    qDebug() << "Material \t\tindex[0] = " << MaterialComponent::family();
//    qDebug() << "Directional \tindex[0] = " << DirectionalLightComponent::family();
//    qDebug() << "PointLight \tindex[0] = " << PointLightComponent::family();
//    qDebug() << "Spotlight \tindex[0] = " << SpotlightComponent::family();
    // Create systems
    mSystems.push_back(std::make_unique<MovementSystem>());
    mSystems.push_back(std::make_unique<DirectionalLightSystem>());
    mSystems.push_back(std::make_unique<PointLightSystem>());
    mSystems.push_back(std::make_unique<SpotlightSystem>());
    mSystems.push_back(std::make_unique<RenderSystem>());
    mSystems.push_back(std::make_unique<playerSystem>());
    mSystems.push_back(std::make_unique<FreeCameraSystem>());
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

void World::updateSystems(const Entity &entity, ComponentMask oldMask)
{
    ComponentMask newMask = mEntityMasks[entity];

    for (auto &sys : mSystems) {
      if (newMask.isNewMatch(oldMask, sys->mSystemMask)) {
        sys->registerEntity(entity);
      } else if (newMask.noLongerMatched(oldMask, sys->mSystemMask)) {
        sys->deRegisterEntity(entity);
      }
    }
}

EntityHandle World::createEntity(const std::string &name)
{
    auto entity = mEntityManager->createEntity(name);
    mEntityMasks.insert(std::make_pair(entity, ComponentMask()));
    return EntityHandle(this, entity);
}

#include <QBitArray>
void World::destroyEntity(const Entity &entity)
{
    // TODO this is not a good system
    auto mask = mEntityMasks[entity].getMask();
    QBitArray test{64};
    for (unsigned int i = 0; i < mask.size(); i++) {
        test[i] = mask[i];
    }
    qDebug() << test;

    for (unsigned int i = 0; i < mask.size(); i++) {
        if (mask[i] == true) {
            switch (i) {
            case 0:
                removeComponent<TransformComponent>(entity);
                break;
            case 1:
                removeComponent<MovementComponent>(entity);
                break;
            case 2:
                removeComponent<MeshComponent>(entity);
                break;
            case 3:
                removeComponent<MaterialComponent>(entity);
                break;
            case 4:
                removeComponent<DirectionalLightComponent>(entity);
                break;
            case 5:
                removeComponent<PointLightComponent>(entity);
                break;
            case 6:
                removeComponent<SpotlightComponent>(entity);
                break;
            case 7:
                removeComponent<InputComponent>(entity);
                break;
            default:
                qDebug() << "something went really wrong";
                break;
            }
        }
    }
    mEntityMasks.erase(entity);
    mEntityManager->destroyEntity(entity);
}

EntityHandle World::getEntity(const std::string &name)
{
    auto e = mEntityManager->getEntity(name);
    return EntityHandle(this, e);
}
