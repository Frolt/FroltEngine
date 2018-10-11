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
#include "viewport.h"
#include "world.h"
#include "meshfactory.h"
#include "entityfactory.h"
#include "materialfactory.h"
#include "paths.h"
#include "shader.h"
#include "a_math.h"

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
    // TODO put somewhere else?
//    mPhongShader.setInt("material.diffuseMap1", 0);
//    mPhongShader.setInt("material.diffuseMap2", 1);
//    mPhongShader.setInt("material.diffuseMap3", 2);
//    mPhongShader.setInt("material.specularMap1", 3);
//    mPhongShader.setInt("material.specularMap2", 4);
//    mPhongShader.setInt("material.specularMap3", 5);
//    mPhongShader.setInt("material.emissionMap", 6);
    // Set  projection matrix
    am::Mat4 perspective = am::Mat4::perspective(am::toRadians(45.0f), mViewport->mAspect, 0.1f, 1000.0f);
    mPhongShader.setMat4("projection", perspective);
    // Create worlds
    mWorld = std::make_unique<World>();
    // Create factories
    mMeshFactory = std::make_unique<MeshFactory>(&mPhongShader);
    mMaterialFactory = std::make_unique<MaterialFactory>();
    mEntityFactory = std::make_unique<EntityFactory>(*mMeshFactory, *mMaterialFactory, *mWorld, *this, mPhongShader);
    // Use shader
    mPhongShader.use();

    // Create entities
    auto player1 = mEntityFactory->createPlayerCube("alexander1", Color::orangeRed);
    auto player2 = mEntityFactory->createPlayerCube("alexander2", Color::blue, am::right() * 2);
    auto player3 = mEntityFactory->createPlayerSphere("alexander3", Color::lime, am::right() * -2);

    auto model1 = mEntityFactory->createModel("model1", Path::models + "alien/alien.fbx", am::Vec{10.0f, 0.0f, 10.0f});
    auto model2 = mEntityFactory->createModel("model2", Path::models + "palm/palm1.obj", am::Vec{-10.0f, 0.0f, -10.0f});

//    auto mathTerrain = mEntityFactory->createMathTerrain("mathTerrain", Color::teal);
//    auto mathTerrain1 = mEntityFactory->createMathTerrain("mathTerrain1", Color::white, -100, 100, am::forward() * -200.0f);
//    auto mathTerrain2 = mEntityFactory->createMathTerrain("mathTerrain2", Color::navy, -100, 100, am::forward() * 200.0f);
//    auto mathTerrain3 = mEntityFactory->createMathTerrain("mathTerrain3", Color::orangeRed, -100, 100, am::right() * 200.0f);
//    auto mathTerrain4 = mEntityFactory->createMathTerrain("mathTerrain4", Color::teal, -100, 100, am::right() * -200.0f);
//    auto mathTerrain5 = mEntityFactory->createMathTerrain("mathTerrain5", Color::maroon, -100, 100, am::Vec{1.0f, 0.0f, 1.0f} * 200.0f);
//    auto mathTerrain6 = mEntityFactory->createMathTerrain("mathTerrain6", Color::lime, -100, 100, am::Vec{1.0f, 0.0f, 1.0f} * -200.0f);
//    auto mathTerrain7 = mEntityFactory->createMathTerrain("mathTerrain7", Color::olive, -100, 100, am::Vec{1.0f, 0.0f, -1.0f} * 200.0f);
//    auto mathTerrain8 = mEntityFactory->createMathTerrain("mathTerrain8", Color::purple, -100, 100, am::Vec{1.0f, 0.0f, -1.0f} * -200.0f);
//    auto lasTerrain = mEntityFactory->createLasTerrain("lasTerrain");
    auto camera = mEntityFactory->createFreeCamera("camera");

    // Testing performance (creates N cubes)
//    for (unsigned int i = 0; i < 1e2; i++) {
//        float randValueX = static_cast<float>(std::rand() % 100 - 50);
//        float randValueY = static_cast<float>(std::rand() % 100 - 50);
//        float randValueZ = static_cast<float>(std::rand() % 100 - 50);
//        auto cube = mEntityFactory->createCube("cube" + std::to_string(i), Color::aqua, am::Vec3{randValueX, randValueY, randValueZ});
//        cube.addComponent(MovementComponent(am::up() * 1.0f));
//    }

    auto dirLight = mEntityFactory->createDirectionalLight("dirLight");
//    auto pointLight1 = mEntityFactory->createPointLight("pointLight1", am::Vec3{0.0f, 20.0f, -100.0f}, Color::white);
//    auto pointLight2 = mEntityFactory->createPointLight("pointLight2", am::Vec3{0.0f, 20.0f, 0.0f}, Color::white);
//    auto pointLight3 = mEntityFactory->createPointLight("pointLight3", am::Vec3{0.0f, 20.0f, 100.0f}, Color::white);
//    auto spotlight1 = mEntityFactory->createSpotlight("spotlight1", am::Vec(-10.0f, 10.0f, 0.0f), -am::up(), Color::white);
//    auto spotlight2 = mEntityFactory->createSpotlight("spotlight2", am::Vec(0.0f, 10.0f, 0.0f), -am::up());
//    auto spotlight3 = mEntityFactory->createSpotlight("spotlight3", am::Vec(10.0f, 20.0f, 0.0f), -am::up());

    // Begin play
    mWorld->init();
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
    // Set  projection matrix
    am::Mat4 perspective = am::Mat4::perspective(am::toRadians(45.0f), mViewport->mAspect, 0.1f, 1000.0f);
    mPhongShader.setMat4("projection", perspective);

    mDeltaTime = mTickTimer.restart() / 1000.0f;
    mWorld->update(mDeltaTime);
    emit mViewport->FPS();
    //-------------------------------------------------------------------
    mViewport->postRender();
}
//-------------------------------------------------------------------
