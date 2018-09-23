#include "engine.h"
#include <QDebug>
#include <QCoreApplication>
#include <QTimer>
#include "viewport.h"
#include "world.h"

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
    mWorld->init();
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

}
