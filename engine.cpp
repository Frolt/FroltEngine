#include "engine.h"
#include <QDebug>
#include <QCoreApplication>
#include <QTimer>
#include "gameobject.h"
#include "viewport.h"
#include "inputcomponent.h"
#include "playerinputcomponent.h"
#include "transformcomponent.h"

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

    mGameObjects.push_back(Factory::makeInputAndTransform(mViewport));
    mGameObjects.push_back(Factory::makeInputAndTransform(mViewport));
    mGameObjects.push_back(Factory::makeInputAndTransform(mViewport));
    mGameObjects.push_back(Factory::makeInputAndTransform(mViewport));
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
    mDeltaTime = static_cast<float>(mTickTimer.restart()) / 1000.0f;
    for (auto &entity : mGameObjects)
        entity->update(mDeltaTime);
    render();
}
