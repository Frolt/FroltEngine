#include "engine.h"
#include <QDebug>
#include <QCoreApplication>
#include <QTimer>
#include "viewport.h"
#include "world.h"
#include "ECS/Systems/movementsystem.h"
#include "ECS/Handles/entityhandle.h"
#include "ECS/Components/transformcomponent.h"
#include "ECS/Components/movementcomponent.h"
#include "ECS/Handles/componenthandle.h"

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


    // Create worlds
    mWorld = std::make_unique<World>();
    // Create systems;
    mWorld->addSystem(std::make_unique<MovementSystem>());
    // Begin play
    mWorld->init();

    // Create entities
    auto player = mWorld->createEntity("alexander");
    player->addComponent(TransformComponent());

    ComponentHandle<TransformComponent> transHandle;
    mWorld->unpack(player->mEntity, transHandle);
    qDebug() << transHandle.mComponent->mScale;
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
    mWorld->update(mDeltaTime);
}
//-------------------------------------------------------------------
