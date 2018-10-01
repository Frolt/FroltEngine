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
    mLightShader = std::make_unique<Shader>(shaderDir + "VertexShader.vert", shaderDir + "LightObject.frag");
    // Create worlds
    mWorld = std::make_unique<World>();
    // Create mesh farm
    mMeshFarm = std::make_unique<MeshFarm>();
    // Begin play
    mWorld->init();

    // Create entities
    auto player = mWorld->createEntity("alexander");
    player.addComponent(TransformComponent());
    player.addComponent(mMeshFarm->getRectangle(mLightShader.get()));
    player.addComponent(MaterialComponent());
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
    mWorld->update(mDeltaTime);
    mViewport->postRender();
}
//-------------------------------------------------------------------
