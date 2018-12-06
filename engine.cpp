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
#include "ECS/Components/collision_component.h"
#include "ECS/Components/skybox_component.h"
#include "viewport.h"
#include "world.h"
#include "meshfactory.h"
#include "entityfactory.h"
#include "materialfactory.h"
#include "path.h"
#include "shader.h"
#include "a_math.h"
#include "EventSystem/eventhandler.h"
#include "EventSystem/collisionevent.h"
#include "inputstate.h"


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
    mSkyboxShader = Shader{Path::shaders + "Skybox.vert", Path::shaders + "Skybox.frag"};
    // Set  projection matrix
    am::Mat4 perspective = am::Mat4::perspective(am::toRadians(45.0f), mViewport->mAspect, 0.1f, 1000.0f);
    mPhongShader.use();
    mPhongShader.setMat4("projection", perspective);
    mSkyboxShader.use();
    mSkyboxShader.setMat4("projection", perspective);
    mPhongShader.use();
    // Create EventHandler
    mEventHandler = std::make_unique<EventHandler>();
    // Create general input object
    mInput = std::make_unique<InputComponent>(&mViewport->mInputState);
    // Create worlds
    mWorld = std::make_unique<World>(this);
    // Create factories
    mMeshFactory = std::make_unique<MeshFactory>(&mPhongShader);
    mMaterialFactory = std::make_unique<MaterialFactory>();
    mEntityFactory = std::make_unique<EntityFactory>(*mMeshFactory, *mMaterialFactory, *mWorld, mViewport->mInputState, mPhongShader);
    // Create scene
    mWorld->makeScene(*mEntityFactory);
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

void Engine::switchCamera()
{
    static bool canPossess{true};
    static bool isPossessingPlayer{false};
    if (isPossessingPlayer)
        mViewport->lockMouseCursor();
    else
        mViewport->releaseMouseCursor();
    if (mInput->keyPressed(Qt::Key_F8) && canPossess) {
        if (isPossessingPlayer) {
            mWorld->activateCamera(mWorld->getEntity("camera"));
            isPossessingPlayer = false;
            canPossess = false;
        } else {
            mWorld->activateCamera(mWorld->getEntity("player"));
            isPossessingPlayer = true;
            canPossess = false;
        }
    } else if (!mInput->keyPressed(Qt::Key_F8)){
        canPossess = true;
    }
}

//-------------------------------------------------------------------
// GAME LOOP
void Engine::gameLoop()
{
    mViewport->preRender();
    //-------------------------------------------------------------------
    mDeltaTime = mTickTimer.restart() / 1000.0f;
    switchCamera();
    mWorld->update(mDeltaTime);
    emit mViewport->FPS();
    //-------------------------------------------------------------------
    mViewport->postRender();
}
//-------------------------------------------------------------------
