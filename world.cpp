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
#include "ECS/Components/free_camera_component.h"
#include "ECS/Components/terrain_component.h"
#include "ECS/Components/model_component.h"
#include "ECS/Components/physics_component.h"
#include "ECS/Components/bspline_component.h"
#include "ECS/Components/trophy_component.h"
#include "ECS/Components/collision_component.h"
#include "ECS/Components/player_component.h"
#include "ECS/Components/ai_component.h"
#include "ECS/Components/third_person_camera_component.h"
#include "ECS/Components/skybox_component.h"
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
#include "ECS/Systems/thirdpersoncamerasystem.h"
#include "ECS/Systems/skyboxsystem.h"
#include "entityfactory.h"
#include "engine.h"
#include <functional>

World::World(Engine *engine)
    : mEngine{*engine}
{
    mComponentManagers.resize(64);
    // Create entity manager
    mEntityManager = std::make_unique<EntityManager>();
    // Create component managers
    mComponentManagers.reserve(20);
    mComponentManagers[TransformComponent::family()] = std::make_unique<ComponentManager<TransformComponent>>(100000);
    mComponentManagers[MovementComponent::family()] = std::make_unique<ComponentManager<MovementComponent>>(100000);
    mComponentManagers[MeshComponent::family()] = std::make_unique<ComponentManager<MeshComponent>>(100000);
    mComponentManagers[MaterialComponent::family()] = std::make_unique<ComponentManager<MaterialComponent>>(100000);
    mComponentManagers[DirectionalLightComponent::family()] = std::make_unique<ComponentManager<DirectionalLightComponent>>(100);
    mComponentManagers[PointLightComponent::family()] = std::make_unique<ComponentManager<PointLightComponent>>(100);
    mComponentManagers[SpotlightComponent::family()] = std::make_unique<ComponentManager<SpotlightComponent>>(100);
    mComponentManagers[InputComponent::family()] = std::make_unique<ComponentManager<InputComponent>>(100000);
    mComponentManagers[FreeCameraComponent::family()] = std::make_unique<ComponentManager<FreeCameraComponent>>(10);
    mComponentManagers[ThirdPersonCameraComponent::family()] = std::make_unique<ComponentManager<ThirdPersonCameraComponent>>(10);
    mComponentManagers[TerrainComponent::family()] = std::make_unique<ComponentManager<TerrainComponent>>(100);
    mComponentManagers[ModelComponent::family()] = std::make_unique<ComponentManager<ModelComponent>>(100000);
    mComponentManagers[PhysicsComponent::family()] = std::make_unique<ComponentManager<PhysicsComponent>>(100000);
    mComponentManagers[BSplineComponent::family()] = std::make_unique<ComponentManager<BSplineComponent>>(100000);
    mComponentManagers[TrophyComponent::family()] = std::make_unique<ComponentManager<TrophyComponent>>(100000);
    mComponentManagers[CollisionComponent::family()] = std::make_unique<ComponentManager<CollisionComponent>>(100000);
    mComponentManagers[PlayerComponent::family()] = std::make_unique<ComponentManager<PlayerComponent>>(5);
    mComponentManagers[AIComponent::family()] = std::make_unique<ComponentManager<AIComponent>>(1000);
    mComponentManagers[SkyboxComponent::family()] = std::make_unique<ComponentManager<SkyboxComponent>>(1);
    // Create systems
    mSystems.reserve(20);
    mSystems.push_back(std::make_unique<MovementSystem>());
    mSystems.push_back(std::make_unique<DirectionalLightSystem>());
    mSystems.push_back(std::make_unique<PointLightSystem>());
    mSystems.push_back(std::make_unique<SpotlightSystem>());
    mSystems.push_back(std::make_unique<PlayerSystem>());
    mSystems.push_back(std::make_unique<FreeCameraSystem>());
    mSystems.push_back(std::make_unique<PhysicsSystem>());
    mSystems.push_back(std::make_unique<AISystem>());
    mSystems.push_back(std::make_unique<CollisionSystem>());
    mSystems.push_back(std::make_unique<CombatSystem>());
    mSystems.push_back(std::make_unique<ThirdPersonCameraSystem>());

    // Order is important
    mSystems.push_back(std::make_unique<SkyboxSystem>());
    mSystems.push_back(std::make_unique<RenderSystem>());
    mSystems.push_back(std::make_unique<ModelRenderSystem>());
    // Set world and eventHandler pointer for all systems
    for (auto &sys : mSystems) {
        sys->setWorld(this);
        sys->setEventHandler(mEngine.mEventHandler.get());
    }
}

World::~World()
{

}

void World::makeScene(EntityFactory &ef)
{
    // vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    // SCENE START
    // vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

    // Player
    auto player = ef.createPlayerModel("player", Color::orangeRed, am::Vec(-25.0f, 0.0f, 0.0f));

    // Terrain
    ef.createMathTerrain("mathTerrain");

    // Enviroment
    ef.createSphere("zeroMarker");
    auto cube0 = ef.createCube("cube0", Color::red, am::Vec{0.0f, 20.0f, 00.0f});
    auto cube1 = ef.createCube("cube1", Color::blue, am::Vec{-15.0f, 0.0f, 0.0f});
    auto cube2 = ef.createCube("cube2", Color::aqua, am::Vec{-5.0f, 0.0f, 0.0f});
    cube0.addEntityComponent(cube1);
    cube1.addEntityComponent(cube2);

//    // AI
//    auto guard = ef.createAIModel("guard", "nanosuit/nanosuit.obj", Color::aqua, am::Vec{0.0f, 20.0f, 0.0f});

    // Camera
    auto camera = ef.createFreeCamera("camera", am::Vec{0.0f, 20.0f, 40.0f});
    activateCamera(player);
    activateCamera(camera);

    // Lights
    ef.createDirectionalLight("dirLight", Color::white);
    ef.createPointLight("pointLight1", am::Vec3{20.0f, 20.0f, -100.0f}, Color::red);
    ef.createPointLight("pointLight2", am::Vec3{-30.0f, 10.0f, 0.0f}, Color::white);
    ef.createPointLight("pointLight3", am::Vec3{60.0f, 20.0f, 100.0f}, Color::orange);
    ef.createSpotlight("spotlight1", am::Vec(-30.0f, 40.0f, 50.0f), -am::up(), Color::white);
    ef.createSpotlight("spotlight2", am::Vec(80.0f, 30.0f, 20.0f), -am::up());
    ef.createSpotlight("spotlight3", am::Vec(-60.0f, 60.0f, -40.0f), -am::up());

    // Skybox
    ef.createSkybox("skybox", "lake");

    // Test rendering performance (creates N cubes)
    for (unsigned int i = 0; i < 1e2; i++) {
        float randValueX = static_cast<float>(std::rand() % 100 - 50);
        float randValueY = static_cast<float>(std::rand() % 100 - 50);
        float randValueZ = static_cast<float>(std::rand() % 100 - 50);
        auto cube = ef.createCube("floatingCube" + std::to_string(i), Color::aqua, am::Vec3{randValueX, randValueY, randValueZ});
        cube.addComponent(MovementComponent(am::up() * 1.0f));
    }

    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // SCENE END
    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

}

void World::beginPlay()
{
    for (auto &sys : mSystems)
        sys->beginPlay();
}

void World::update(float deltaTime)
{
    for (auto &sys : mSystems)
        sys->update(deltaTime);
}

void World::updateSystems(EntityID entity, ComponentMask oldMask)
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

EntityHandle World::createEntity(const std::string &name, Entity *parent)
{
    Entity *entity = mEntityManager->createEntity(name);
    if (parent) {
        parent->mChild = entity;
        entity->mParent = parent;
    }
    mEntityMasks[entity->mID] = ComponentMask();
    return EntityHandle(this, entity);
}

void World::destroyEntity(EntityID entity)
{
    Entity *entityPtr = mEntityManager->getEntity(entity);
    // Update the parent/child relationship
    if (entityPtr->mParent)
        entityPtr->mParent->mChild = nullptr;
    if (entityPtr->mChild)
        destroyEntity(*entityPtr->mChild);

    // Destroy all components belonging to entity
    for (auto &manager : mComponentManagers) {
        if (!manager)
            break;
        manager->destroyComponent(entity);
    }

    // Update mask
    ComponentMask oldMask = mEntityMasks[entityPtr->mID];
    mEntityMasks[entityPtr->mID].reset();
    updateSystems(entityPtr->mID, oldMask);

    // Destroy mask and entity
    mEntityMasks.erase(entityPtr->mID);
    mEntityManager->destroyEntity(entityPtr->mID);
}

void World::destroyEntity(const Entity &entity)
{
    // Update the parent/child relationship
    if (entity.mParent)
        entity.mParent->mChild = nullptr;
    if (entity.mChild)
        destroyEntity(*entity.mChild);

    // Destroy all components belonging to entity
    for (auto &manager : mComponentManagers) {
        if (!manager)
            break;
        manager->destroyComponent(entity.mID);
    }

    // Update mask
    ComponentMask oldMask = mEntityMasks[entity.mID];
    mEntityMasks[entity.mID].reset();
    updateSystems(entity.mID, oldMask);

    // Destroy mask and entity
    mEntityMasks.erase(entity.mID);
    mEntityManager->destroyEntity(entity.mID);
}

EntityHandle World::getEntity(EntityID entity)
{
    Entity *entityPtr = mEntityManager->getEntity(entity);
    return EntityHandle(this, entityPtr);
}

EntityHandle World::getEntity(const std::string &name)
{
    Entity *entity = mEntityManager->getEntity(name);
    return EntityHandle(this, entity);
}

Entity *World::getEntityPtr(EntityID entity)
{
    return mEntityManager->getEntity(entity);
}

Entity *World::getEntityPtr(const std::string &name)
{
    return mEntityManager->getEntity(name);
}

bool World::entityExist(EntityID entity)
{
    return mEntityManager->entityExist(entity);
}

bool World::entityExist(const std::string &name)
{
    return mEntityManager->entityExist(name);
}

unsigned int World::getNumberOfEntities()
{
    return static_cast<unsigned int>(mEntityManager->numOfEntities());
}

void World::activateCamera(EntityID entity)
{
    auto *freeCamManager = static_cast<ComponentManager<FreeCameraComponent> *>(mComponentManagers[FreeCameraComponent::family()].get());
    auto *thirdCamManager = static_cast<ComponentManager<ThirdPersonCameraComponent> *>(mComponentManagers[ThirdPersonCameraComponent::family()].get());

    freeCamManager->iterateAll([](FreeCameraComponent &cameraComp) { cameraComp.mActive = false; });
    thirdCamManager->iterateAll([](ThirdPersonCameraComponent &cameraComp) { cameraComp.mActive = false; });
    if (hasComponent<FreeCameraComponent>(entity)) {
        auto camera = freeCamManager->getComponent(entity);
        camera->mActive = true;
    } else if (hasComponent<ThirdPersonCameraComponent>(entity)) {
        auto camera = thirdCamManager->getComponent(entity);
        camera->mActive = true;
    } else {
        qDebug() << "ERROR:: entity does not have a camera";
    }
}
