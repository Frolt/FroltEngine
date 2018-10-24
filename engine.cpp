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
#include "viewport.h"
#include "world.h"
#include "meshfactory.h"
#include "entityfactory.h"
#include "materialfactory.h"
#include "paths.h"
#include "shader.h"
#include "a_math.h"

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
    mPhongShader = Shader{Path::shaders + "VertexShader.vert", Path::shaders + "LightObject.frag"};
    // Set  projection matrix
    am::Mat4 perspective = am::Mat4::perspective(am::toRadians(45.0f), mViewport->mAspect, 0.1f, 1000.0f);
    mPhongShader.setMat4("projection", perspective);
    // Create worlds
    mWorld = std::make_unique<World>(this);
    // Create factories
    mMeshFactory = std::make_unique<MeshFactory>(&mPhongShader);
    mMaterialFactory = std::make_unique<MaterialFactory>();
    mEntityFactory = std::make_unique<EntityFactory>(*mMeshFactory, *mMaterialFactory, *mWorld, *this, mPhongShader);
    // Use shader
    mPhongShader.use();

    // Create entities
//    auto player1 = mEntityFactory->createPlayerSphere("alexander1", Color::orangeRed);
//    player1.addComponent(CollisionComponent());

    // TESTING
//    auto physicsBall1 =  mEntityFactory->createPhysicsBall("physicsBall1", Color::purple, am::Vec{0.0f, 20.0f, -18.0f});
//    auto physicsBall2 =  mEntityFactory->createPhysicsBall("physicsBall2", Color::purple, am::Vec{-2.0f, 30.0f, -8.0f});
//    auto physicsBall3 =  mEntityFactory->createPhysicsBall("physicsBall3", Color::purple, am::Vec{-10.0f, 20.0f, -2.0f});
//    auto physicsBall4 =  mEntityFactory->createPhysicsBall("physicsBall4", Color::purple, am::Vec{-15.0f, 17.0f, -10.0f});
//    auto physicsBall5 =  mEntityFactory->createPhysicsBall("physicsBall5", Color::purple, am::Vec{6.0f, 10.0f, 11.0f});

    auto model1 = mEntityFactory->createModel("model1", Path::models + "alien/alien.fbx", am::Vec{20.0f, 20.0f, 10.0f});
    auto model2 = mEntityFactory->createModel("model2", Path::models + "nanosuit/nanosuit.obj", am::Vec{-10.0f, 0.0f, -10.0f});

//    auto lasTerrain = mEntityFactory->createLasTerrain("lasTerrain", Color::blue);
    mTerrain1 = mEntityFactory->createMathTerrain("mathTerrain", Color::silver);
    auto camera = mEntityFactory->createFreeCamera("camera", am::Vec{0.0f, 20.0f, 40.0f});
    auto AISphere = mEntityFactory->createAISphere("AISphere", Color::aqua, am::Vec{0.0f, 20.0f, 0.0f});

    // Testing performance (creates N cubes)
    for (unsigned int i = 0; i < 1e1; i++) {
        float randValueX = static_cast<float>(std::rand() % 100 - 50);
        float randValueY = static_cast<float>(std::rand() % 100 - 50);
        float randValueZ = static_cast<float>(std::rand() % 100 - 50);
        auto cube = mEntityFactory->createCube("cube" + std::to_string(i), Color::aqua, am::Vec3{randValueX, randValueY, randValueZ});
        cube.addComponent(MovementComponent(am::up() * 1.0f));
    }

    auto dirLight = mEntityFactory->createDirectionalLight("dirLight");
    auto pointLight1 = mEntityFactory->createPointLight("pointLight1", am::Vec3{20.0f, 20.0f, -100.0f}, Color::red);
//    pointLight1.addComponent(MovementComponent(am::forward() * 10.0f));
    auto pointLight2 = mEntityFactory->createPointLight("pointLight2", am::Vec3{-30.0f, 20.0f, 0.0f}, Color::yellow);
    auto pointLight3 = mEntityFactory->createPointLight("pointLight3", am::Vec3{60.0f, 20.0f, 100.0f}, Color::orange);
    auto spotlight1 = mEntityFactory->createSpotlight("spotlight1", am::Vec(-30.0f, 40.0f, 50.0f), -am::up(), Color::white);
    auto spotlight2 = mEntityFactory->createSpotlight("spotlight2", am::Vec(80.0f, 30.0f, 20.0f), -am::up());
    auto spotlight3 = mEntityFactory->createSpotlight("spotlight3", am::Vec(-60.0f, 60.0f, -40.0f), -am::up());

    // Begin play
    mWorld->init();
}

void Engine::startGameLoop()
{
    mTimer.start();
    mTickTimer.start();
    mGameLoopTimer->start(1);
}

void Engine::render()
{
    mViewport->preRender();
    //-------------------------------------------------------------------
    // TODO free rendering from update() function
    //-------------------------------------------------------------------
    mViewport->postRender();
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
    // Set  projection matrix
    am::Mat4 perspective = am::Mat4::perspective(am::toRadians(45.0f), mViewport->mAspect, 0.1f, 1000.0f);
    mPhongShader.setMat4("projection", perspective);

    mDeltaTime = mTickTimer.restart() / 1000.0f;
    mWorld->update(mDeltaTime);
    emit mViewport->FPS();
    //-------------------------------------------------------------------
    mViewport->postRender();
}
//-------------------------------------------------------------------
