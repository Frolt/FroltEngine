#include "engine.h"
#include <QDebug>
#include <QCoreApplication>
#include <QTimer>
#include "entity.h"
#include "viewport.h"
#include "inputcomponent.h"
#include "playerinputcomponent.h"

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
    connect(mGameLoopTimer, SIGNAL(timeout()), this, SLOT(gameLoop()));

    mEntities.push_back(std::make_shared<Entity>(std::make_shared<PlayerInputComponent>(mViewport)));
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

void Engine::gameLoop()
{
    for (auto &entity : mEntities)
        entity->update();
    render();
}
