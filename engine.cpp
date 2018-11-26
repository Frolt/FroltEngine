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
#include "ECS/Components/trophy_component.h"
#include "ECS/Components/collision_component.h"
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
    // Create worlds
    mWorld = std::make_unique<World>(this);
    // Create factories
    mMeshFactory = std::make_unique<MeshFactory>(&mPhongShader);
    mMaterialFactory = std::make_unique<MaterialFactory>();
    mEntityFactory = std::make_unique<EntityFactory>(*mMeshFactory, *mMaterialFactory, *mWorld, mViewport->mInputState, mPhongShader);

    // SCENE START
    // ---------------------------------------------------------------------------------------

    mWorld->makeScene(*mEntityFactory);

    // Guard path
    auto startPos = mEntityFactory->createSphere("startPos", Color::green, am::Vec3{-20.0f, -15.0f, 0.0f});
    auto endPos = mEntityFactory->createSphere("endPos", Color::red, am::Vec3{20.0f, 18.0f, 0.0f});
    mTrophies.push_back(mEntityFactory->createModel("trophy1", "trophy/treasure_chest.obj", am::Vec{-10.0f, -28.0f, -10.0f}));
    mTrophies.back().addComponent(CollisionComponent());
    mTrophies.push_back(mEntityFactory->createModel("trophy2", "trophy/treasure_chest.obj", am::Vec{0.0f, 1.0f, 10.0f}));
    mTrophies.back().addComponent(CollisionComponent());
    mTrophies.push_back(mEntityFactory->createModel("trophy3", "trophy/treasure_chest.obj", am::Vec{10.0f, 10.0f, -3.0f}));
    mTrophies.back().addComponent(CollisionComponent());

    // SCENE END
    // ---------------------------------------------------------------------------------------

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

//-------------------------------------------------------------------
// GAME LOOP
void Engine::gameLoop()
{
    mViewport->preRender();
    //-------------------------------------------------------------------
    mDeltaTime = mTickTimer.restart() / 1000.0f;
    mWorld->update(mDeltaTime);
    emit mViewport->FPS();
    //-------------------------------------------------------------------
    mViewport->postRender();
}
//-------------------------------------------------------------------
