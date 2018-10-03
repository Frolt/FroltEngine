#include "engine.h"
#include <QDebug>
#include <QCoreApplication>
#include <QTimer>
#include "ECS/Systems/movementsystem.h"
#include "ECS/Handles/entityhandle.h"
#include "ECS/Components/transform_component.h"
#include "ECS/Components/movement_component.h"
#include "ECS/Components/mesh_component.h"
#include "ECS/Components/material_component.h"
#include "ECS/Handles/componenthandle.h"
#include "viewport.h"
#include "world.h"
#include "meshfarm.h"
#include "paths.h"

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
    mPhongShader = std::make_unique<Shader>(shaderDir + "VertexShader.vert", shaderDir + "LightObject.frag");
    // Create worlds
    mWorld = std::make_unique<World>();
    // Create mesh farm
    mMeshFarm = std::make_unique<MeshFarm>(mPhongShader.get());
    // Begin play
    mWorld->init();

    // Create entities
    auto player = mWorld->createEntity("alexander");
    player.addComponent(TransformComponent(am::Vec{1.0f, 0.0f, 0.0f}));
    player.addComponent(mMeshFarm->createCube(mPhongShader.get()));
    player.addComponent(MaterialComponent());

    auto ole = mWorld->createEntity("ole");
    ole.addComponent(TransformComponent(am::Vec{-1.0f, 0.0f, 0.0f}));
    ole.addComponent(MovementComponent());
    ole.addComponent(MaterialComponent());
    ole.addComponent(mMeshFarm->createRectangle());
}

void Engine::startGameLoop()
{
    mTimer.start();
    mTickTimer.start();
    mGameLoopTimer->start(16);
}

void Engine::render()
{
    mViewport->preRender();
    //-------------------------------------------------------------------

    // set shader uniforms?

    // draw calls

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

    // SET VIEW AND PROJECTION MATRIX
    am::Mat4 perspective = am::Mat4::perspective(am::toRadians(45.0f), mViewport->mAspect, 0.1f, 1000.0f);
    auto view = am::Mat4::lookAt(am::Vec{0.0f, 5.0f, 10.0f}, am::Vec{0.0f, 0.0f, 0.0f}, am::up());
    mPhongShader->use();
    mPhongShader->setMat4("projection", perspective);
    mPhongShader->setMat4("view", view);

    mWorld->update(mDeltaTime);
    mViewport->postRender();
}
//-------------------------------------------------------------------
