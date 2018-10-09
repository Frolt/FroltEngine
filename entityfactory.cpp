#include "entityfactory.h"
#include "ECS/entity.h"
#include "ECS/Handles/entityhandle.h"
#include "ECS/Handles/componenthandle.h"
#include "ECS/Components/transform_component.h"
#include "ECS/Components/movement_component.h"
#include "ECS/Components/mesh_component.h"
#include "ECS/Components/material_component.h"
#include "ECS/Components/directionallight_component.h"
#include "ECS/Components/pointlight_component.h"
#include "ECS/Components/spotlight_component.h"
#include "ECS/Components/input_component.h"
#include "ECS/Components/camera_component.h"
#include "ECS/Components/free_camera_component.h"
#include "ECS/Components/math_terrain_component.h"
#include "meshfactory.h"
#include "world.h"
#include "engine.h"
#include "viewport.h"
#include "octahedron.h"
#include "mathterraingenerator.h"


EntityFactory::EntityFactory(MeshFactory &meshFactory, World &world, Engine &engine, Shader &shader)
    : mMeshFactory{meshFactory}, mWorld{world}, mEngine{engine}, mDefaultShader{shader}
{

}

EntityHandle EntityFactory::createDirectionalLight(const std::string &name, const am::Vec3 &color)
{
    // Consists of: DirectionalLight
    auto entity = mWorld.createEntity(name);
    DirectionalLightComponent dirLight(-am::up(), am::Vec{0.1}, am::Vec{1});
    dirLight.mDiff = color;
    dirLight.mAmb = color * 0.1f;
    dirLight.mShader = mDefaultShader;
    entity.addComponent(dirLight);
    return EntityHandle(&mWorld, entity());
}

EntityHandle EntityFactory::createPointLight(const std::string &name, const am::Vec3 &pos, const am::Vec3 &color)
{
    // Consists of: PointLight, Transform
    auto entity = mWorld.createEntity(name);
    PointLightComponent pointLight{am::Vec{0.1}, am::Vec{1}};
    pointLight.mShader = mDefaultShader;
    pointLight.mDiff = color;
    pointLight.mAmb = color * 0.1f;
    TransformComponent transform;
    transform.mPosition = pos;
    entity.addComponent(pointLight);
    entity.addComponent(transform);
    return EntityHandle(&mWorld, entity());
}

EntityHandle EntityFactory::createSpotlight(const std::string &name, const am::Vec3 &pos, const am::Vec3 &color)
{
    // Consists of: Spotlight, Transform
    auto entity = mWorld.createEntity(name);
    SpotlightComponent spotlight(-am::forward(), am::Vec{0.1}, am::Vec{1});
    spotlight.mShader = mDefaultShader;
    spotlight.mDiff = color;
    spotlight.mAmb = color * 0.1f;
    TransformComponent transform;
    transform.mPosition = pos;
    entity.addComponent(spotlight);
    entity.addComponent(transform);
    return EntityHandle(&mWorld, entity());
}

EntityHandle EntityFactory::createCube(const std::string &name, const am::Vec3 &color, const am::Vec3 &pos)
{
    // Consists of: Mesh, Material, Transform
    auto entity = mWorld.createEntity(name);
    MeshComponent mesh = mMeshFactory.createCube();
    MaterialComponent material;
    material.mDiffuseColor = color;
    TransformComponent transform;
    transform.mPosition = pos;
    entity.addComponent(mesh);
    entity.addComponent(material);
    entity.addComponent(transform);
    return EntityHandle(&mWorld, entity());
}

EntityHandle EntityFactory::createSphere(const std::string &name, const am::Vec3 &color, const am::Vec3 &pos)
{
    // Consists of: Mesh, Material, Transform
    auto entity = mWorld.createEntity(name);
    MeshComponent mesh = mMeshFactory.createSphere();
    MaterialComponent material;
    material.mDiffuseColor = color;
    TransformComponent transform;
    transform.mPosition = pos;
    entity.addComponent(mesh);
    entity.addComponent(material);
    entity.addComponent(transform);
    return EntityHandle(&mWorld, entity());
}

EntityHandle EntityFactory::createPlayerCube(const std::string &name, const am::Vec3 &color, const am::Vec3 &pos)
{
    // Consists of: Mesh, Material, Transform, Movement, Input
    auto entity = mWorld.createEntity(name);
    MeshComponent mesh = mMeshFactory.createCube();
    MaterialComponent material;
    material.mDiffuseColor = color;
    TransformComponent transform;
    transform.mPosition = pos;
    MovementComponent movement;
    InputComponent input(&mEngine.mViewport->mInputState);
    entity.addComponent(mesh);
    entity.addComponent(material);
    entity.addComponent(transform);
    entity.addComponent(movement);
    entity.addComponent(input);
    return EntityHandle(&mWorld, entity());
}

EntityHandle EntityFactory::createPlayerSphere(const std::string &name, const am::Vec3 &color, const am::Vec3 &pos)
{
    // Consists of: Mesh, Material, Transform, Movement, Input
    auto entity = mWorld.createEntity(name);
    MeshComponent mesh = mMeshFactory.createSphere();
    MaterialComponent material;
    material.mDiffuseColor = color;
    TransformComponent transform;
    transform.mPosition = pos;
    MovementComponent movement;
    InputComponent input(&mEngine.mViewport->mInputState);
    entity.addComponent(mesh);
    entity.addComponent(material);
    entity.addComponent(transform);
    entity.addComponent(movement);
    entity.addComponent(input);
    return EntityHandle(&mWorld, entity());
}

EntityHandle EntityFactory::createFreeCamera(const std::string &name, const am::Vec3 &pos)
{
    // Consists of: Transform, Movement, Input, Camera, FreeCamera
    auto entity = mWorld.createEntity(name);
    TransformComponent transform;
    transform.mPosition = pos;
    MovementComponent movement;
    InputComponent input(&mEngine.mViewport->mInputState);
    CameraComponent camera(mDefaultShader);
    FreeCameraComponent freeCamera;
    entity.addComponent(transform);
    entity.addComponent(movement);
    entity.addComponent(input);
    entity.addComponent(camera);
    entity.addComponent(freeCamera);
    return EntityHandle(&mWorld, entity());
}

EntityHandle EntityFactory::createMathTerrain(const std::string &name, const am::Vec3 &color, int min, int max, const am::Vec3 &pos)
{
    // TODO snakk med ole, constuctor i struct?
    // Consists of: Transform, Mesh, Material, MathTerrain
    MathTerrainGenerator terrainGen{min, max};
    auto entity = mWorld.createEntity(name);
    TransformComponent transform;
    transform.mPosition = pos;
    MeshComponent mesh = mMeshFactory.createTerrain(terrainGen.mVertices, terrainGen.mIndices);
    MaterialComponent material;
    material.mDiffuseColor = color;
    MathTerrainComponent terrain;
    terrain.mTriangles = terrainGen.mTriangles;
    terrain.mVertices = terrainGen.mVertices;
    entity.addComponent(transform);
    entity.addComponent(mesh);
    entity.addComponent(material);
    entity.addComponent(terrain);
    return EntityHandle(&mWorld, entity());
}
