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
#include "viewport.h"
#include "world.h"
#include "meshfarm.h"
#include "objectfarm.h"
#include "paths.h"
#include "shader.h"

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
    // Create worlds
    mWorld = std::make_unique<World>();
    // Create farms
    mMeshFarm = std::make_unique<MeshFarm>(&mPhongShader);
    mObjectFarm = std::make_unique<ObjectFarm>(*mMeshFarm, *mWorld, mPhongShader);
    // Begin play
    mWorld->init();

    // Create entities
    auto player = mObjectFarm->createSphere("alexander");

    // Testing performance (creates N cubes)
    for (unsigned int i = 0; i < 1e3; i++) {
        float randValueX = static_cast<float>(std::rand() % 100 - 50);
        float randValueY = static_cast<float>(std::rand() % 100 - 50);
        float randValueZ = static_cast<float>(std::rand() % 100 - 50);
        auto cube = mObjectFarm->createCube("cube" + std::to_string(i), Colors::aqua, am::Vec3{randValueX, randValueY, randValueZ});
        cube.addComponent(MovementComponent(am::up() * 1.0f));
    }
    mPhongShader.use();

    auto dirLight = mObjectFarm->createDirectionalLight("dirLight");
    auto pointLight = mObjectFarm->createPointLight("pointLight", am::Vec3{-10.0f, 5.0f, 0.0f});
    auto spotlight = mObjectFarm->createSpotlight("spotlight", am::forward() * 20.0f);
}

void Engine::startGameLoop()
{
    mTimer.start();
    mTickTimer.start();
    mGameLoopTimer->start(0);
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
    mDeltaTime = mTickTimer.restart() / 1000.0f;

    // Set view and projection matrix
    am::Mat4 perspective = am::Mat4::perspective(am::toRadians(45.0f), mViewport->mAspect, 0.1f, 1000.0f);
//    auto view = am::Mat4::lookAt(am::Vec{0.0f, 100.0f, 200.0f}, am::Vec{0.0f, 0.0f, 0.0f}, am::up());
    auto view = am::Mat4::lookAt(am::Vec{10.0f, 5.0f, 10.0f}, am::Vec{0.0f, 0.0f, 0.0f}, am::up());
    mPhongShader.setMat4("projection", perspective);
    mPhongShader.setMat4("view", view);
    mPhongShader.setVec3("camPos", am::Vec{10.0f, 5.0f, 10.0f});

    mWorld->update(mDeltaTime);
    emit mViewport->FPS();

    //-------------------------------------------------------------------
    mViewport->postRender();
}
//-------------------------------------------------------------------
