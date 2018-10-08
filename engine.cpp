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
#include "meshfactory.h"
#include "entityfactory.h"
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
    // Create factories
    mMeshFactory = std::make_unique<MeshFactory>(&mPhongShader);
    mEntityFactory = std::make_unique<EntityFactory>(*mMeshFactory, *mWorld, *this, mPhongShader);
    // Begin play
    mWorld->init();

    // Create entities
//    auto player1 = mEntityFactory->createPlayerCube("alexander1");
//    auto player2 = mEntityFactory->createPlayerCube("alexander2", Colors::blue, am::right() * 2);
//    auto player3 = mEntityFactory->createPlayerSphere("alexander3", Colors::green, am::right() * -2);

    auto camera = mEntityFactory->createFreeCamera("camera");

    // Testing performance (creates N cubes)
    for (unsigned int i = 0; i < 1e2; i++) {
        float randValueX = static_cast<float>(std::rand() % 100 - 50);
        float randValueY = static_cast<float>(std::rand() % 100 - 50);
        float randValueZ = static_cast<float>(std::rand() % 100 - 50);
        auto cube = mEntityFactory->createCube("cube" + std::to_string(i), Colors::aqua, am::Vec3{randValueX, randValueY, randValueZ});
        cube.addComponent(MovementComponent(am::up() * 1.0f));
    }
    mPhongShader.use();

    auto dirLight = mEntityFactory->createDirectionalLight("dirLight");
    auto pointLight = mEntityFactory->createPointLight("pointLight", am::Vec3{-10.0f, 5.0f, 0.0f});
    auto spotlight = mEntityFactory->createSpotlight("spotlight", am::forward() * 20.0f);
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
    mDeltaTime = mTickTimer.restart() / 1000.0f;

    // Set view and projection matrix
    am::Mat4 perspective = am::Mat4::perspective(am::toRadians(45.0f), mViewport->mAspect, 0.1f, 1000.0f);
    mPhongShader.setMat4("projection", perspective);

    mWorld->update(mDeltaTime);
    emit mViewport->FPS();

    //-------------------------------------------------------------------
    mViewport->postRender();
}
//-------------------------------------------------------------------
