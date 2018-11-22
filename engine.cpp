#include "engine.h"
#include <QDebug>
#include <QCoreApplication>
#include <QTimer>
#include "ECS/Handles/entityhandle.h"
#include "ECS/Handles/componenthandle.h"
#include "ECS/Components/transform_component.h"
#include "ECS/Components/movement_component.h"
#include "ECS/Components/mesh_component.h"
#include "ECS/Components/material_component.h"
#include "ECS/Components/directionallight_component.h"
#include "ECS/Components/pointlight_component.h"
#include "ECS/Components/spotlight_component.h"
#include "ECS/Components/camera_component.h"
#include "ECS/Components/terrain_component.h"
#include "ECS/Components/input_component.h"
#include "ECS/Components/physics_component.h"
#include "ECS/Components/trophy_component.h"
#include "ECS/Components/collision_component.h"
#include "viewport.h"
#include "world.h"
#include "meshfactory.h"
#include "entityfactory.h"
#include "materialfactory.h"
#include "paths.h"
#include "shader.h"
#include "a_math.h"
#include "EventSystem/eventhandler.h"
#include "EventSystem/collisionevent.h"

Engine::Engine(Viewport *viewport, QObject *parent)
    : QObject(parent),
      mViewport{viewport}
{
    mGameLoopTimer = new QTimer(this);
    initialize();
    startGameLoop();
}

void Engine::initialize()
{
    // Connect timer with gameLoop() function
    connect(mGameLoopTimer, SIGNAL(timeout()), this, SLOT(gameLoop()));

    // Create shaders
    mPhongShader = Shader{Path::shaders + "VertexShader.vert", Path::shaders + "PhongShader.frag"};
    // Use shader
    mPhongShader.use();
    // Set  projection matrix
    am::Mat4 perspective = am::Mat4::perspective(am::toRadians(45.0f), mViewport->mAspect, 0.1f, 1000.0f);
    mPhongShader.setMat4("projection", perspective);
    // Create EventHandler
    mEventHandler = std::make_unique<EventHandler>();
    // Create worlds
    mWorld = std::make_unique<World>(this);
    // Create factories
    mMeshFactory = std::make_unique<MeshFactory>(&mPhongShader);
    mMaterialFactory = std::make_unique<MaterialFactory>();
    mEntityFactory = std::make_unique<EntityFactory>(*mMeshFactory, *mMaterialFactory, *mWorld, *this, mPhongShader);

    // SCENE START
    // ---------------------------------------------------------------------------------------

    // Create entities
    auto player = mEntityFactory->createPlayerModel("player", Color::orangeRed, am::Vec(-25.0f, 0.0f, 0.0f));
    player.addComponent(PhysicsComponent());
    player.addComponent(CollisionComponent());
    auto sphere = mEntityFactory->createSphere("sphere", Color::red, am::Vec{0.0f, 20.0f, 0.0f});
    auto cube1 = mEntityFactory->createCube("cube1", Color::blue, am::Vec{-10.0f, 0.0f, 0.0f});
    auto cube2 = mEntityFactory->createCube("cube2", Color::aqua, am::Vec{0.0f, 10.0f, 0.0f});
    sphere.addEntityComponent(cube1);
    cube1.addEntityComponent(cube2);
    sphere.setRelativeScale(am::Vec(2.0f, 2.0f, 2.0f));
    sphere.setRelativeRotation(am::Vec(0.0f, 0.0f, 0.0f));
    cube2.addRelativeLocation(am::forward() * 10.0f);
    cube2.addRelativeScale(am::Vec(3));
    auto testCube1 = player.createEntityComponent("testCube1");
    testCube1.addComponent(TransformComponent(am::up() * 10.0f));
    testCube1.addComponent(MaterialComponent());
    testCube1.addComponent(mMeshFactory->createCube());
    auto testCube2 = player.createEntityComponent("testCube2");
    testCube2.addComponent(TransformComponent(am::Vec{-10.0f, 10.0f, 0.0f}));
    testCube2.addComponent(MaterialComponent(Color::aqua));
    testCube2.addComponent(mMeshFactory->createCube());
    auto testCube3 = player.createEntityComponent("testCube3");
    testCube3.addComponent(TransformComponent(am::Vec{10.0f, 10.0f, 0.0f}));
    testCube3.addComponent(MaterialComponent(Color::black, 50));
    testCube3.addComponent(mMeshFactory->createCube());

    sphere.setRelativeRotation(am::Rotator(45.0f, 0.0f, 0.0f));
//    sphere.destroy();


    am::Vec3 rot;
    rot.yaw = 1.0f;
    rot.x = 1.0f;

    am::Vec3 col;
    col.r = 1.0f;




//    auto model1 = mEntityFactory->createModel("model1", "alien/alien.fbx", am::Vec{20.0f, 20.0f, 10.0f});
//    auto model2 = mEntityFactory->createModel("model2", "nanosuit/nanosuit.obj", am::Vec{-10.0f, 0.0f, -10.0f});

    mTerrain1 = mEntityFactory->createMathTerrain("mathTerrain");

    // TEST FLOOR
//    auto floor = mEntityFactory->createCube("floor");
//    ch::Transform transform;
//    ch::Material material;
//    mWorld->unpack(floor, transform, material);
//    transform().mScale = am::Vec3(50.0f, 1.0f, 50.0f);
//    transform().mPosition = -am::up() * 2.0f;

    auto camera = mEntityFactory->createFreeCamera("camera", am::Vec{0.0f, 20.0f, 40.0f});
    auto AISphere = mEntityFactory->createAIModel("AISphere", "nanosuit/nanosuit.obj", Color::aqua, am::Vec{0.0f, 20.0f, 0.0f});
    AISphere.addComponent(CollisionComponent());
    AISphere.addComponent(PhysicsComponent());

    mWorld->activateCamera(player);
    mWorld->activateCamera(camera);

    auto startPos = mEntityFactory->createSphere("startPos", Color::green, am::Vec3{-20.0f, -15.0f, 0.0f});
    auto endPos = mEntityFactory->createSphere("endPos", Color::red, am::Vec3{20.0f, 18.0f, 0.0f});
    mTrophies.push_back(mEntityFactory->createModel("trophy1", "trophy/treasure_chest.obj", am::Vec{-10.0f, -28.0f, -10.0f}));
    mTrophies.back().addComponent(CollisionComponent());
    mTrophies.push_back(mEntityFactory->createModel("trophy2", "trophy/treasure_chest.obj", am::Vec{0.0f, 1.0f, 10.0f}));
    mTrophies.back().addComponent(CollisionComponent());
    mTrophies.push_back(mEntityFactory->createModel("trophy3", "trophy/treasure_chest.obj", am::Vec{10.0f, 10.0f, -3.0f}));
    mTrophies.back().addComponent(CollisionComponent());

//    // Testing performance (creates N cubes)
//    for (unsigned int i = 0; i < 1e1; i++) {
//        float randValueX = static_cast<float>(std::rand() % 100 - 50);
//        float randValueY = static_cast<float>(std::rand() % 100 - 50);
//        float randValueZ = static_cast<float>(std::rand() % 100 - 50);
//        auto cube = mEntityFactory->createCube("cube" + std::to_string(i), Color::aqua, am::Vec3{randValueX, randValueY, randValueZ});
//        cube.addComponent(MovementComponent(am::up() * 1.0f));
//    }

    auto dirLight = mEntityFactory->createDirectionalLight("dirLight", Color::white);
    auto pointLight1 = mEntityFactory->createPointLight("pointLight1", am::Vec3{20.0f, 20.0f, -100.0f}, Color::red);
    auto pointLight2 = mEntityFactory->createPointLight("pointLight2", am::Vec3{-30.0f, 10.0f, 0.0f}, Color::white);
    auto pointLight3 = mEntityFactory->createPointLight("pointLight3", am::Vec3{60.0f, 20.0f, 100.0f}, Color::orange);
    auto spotlight1 = mEntityFactory->createSpotlight("spotlight1", am::Vec(-30.0f, 40.0f, 50.0f), -am::up(), Color::white);
    auto spotlight2 = mEntityFactory->createSpotlight("spotlight2", am::Vec(80.0f, 30.0f, 20.0f), -am::up());
    auto spotlight3 = mEntityFactory->createSpotlight("spotlight3", am::Vec(-60.0f, 60.0f, -40.0f), -am::up());

    // SCENE END
    // ---------------------------------------------------------------------------------------

    // Begin play
    mWorld->beginPlay();
}

void Engine::startGameLoop()
{
    mTimer.start();
    mTickTimer.start();
    mGameLoopTimer->start(1);
}

float Engine::getTime()
{
    return mTimer.elapsed() / 1000.0f;
}

//-------------------------------------------------------------------
// GAME LOOP
void Engine::gameLoop()
{
    mViewport->preRender();
    //-------------------------------------------------------------------
    mDeltaTime = mTickTimer.restart() / 1000.0f;
    mWorld->update(mDeltaTime);
    emit mViewport->FPS();
    //-------------------------------------------------------------------
    mViewport->postRender();
}
//-------------------------------------------------------------------
