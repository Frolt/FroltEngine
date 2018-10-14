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
#include "ECS/Components/terrain_component.h"
#include "ECS/Components/model_component.h"
#include "ECS/Components/physics_component.h"
#include "meshfactory.h"
#include "materialfactory.h"
#include "world.h"
#include "engine.h"
#include "viewport.h"
#include "octahedron.h"
#include "mathterraingenerator.h"
#include "lazterraingenerator.h"


EntityFactory::EntityFactory(MeshFactory &meshFactory, MaterialFactory &materialFactory, World &world, Engine &engine, Shader &shader)
    : mMeshFactory{meshFactory}, mMaterialFactory{materialFactory}, mWorld{world}, mEngine{engine}, mDefaultShader{shader}
{

}

EntityHandle EntityFactory::createDirectionalLight(const std::string &name, const am::Vec3 &color)
{
    // Consists of: DirectionalLight
    auto entity = mWorld.createEntity(name);
    DirectionalLightComponent dirLight(-am::up(), am::Vec{0.1}, am::Vec{1});
    dirLight.mDiff = color;
    dirLight.mAmb = color * 0.0f;
    dirLight.mShader = mDefaultShader;
    entity.addComponent(dirLight);
    return entity;
}

EntityHandle EntityFactory::createPointLight(const std::string &name, const am::Vec3 &pos, const am::Vec3 &color)
{
    // Consists of: PointLight, Transform
    static int lightInstance{0};
    auto entity = mWorld.createEntity(name);
    PointLightComponent pointLight{lightInstance++};
    pointLight.mShader = mDefaultShader;
    pointLight.mDiff = color;
    TransformComponent transform;
    transform.mPosition = pos;
    MeshComponent mesh{mMeshFactory.createSphere()};
    MaterialComponent material;
    material.mIsLight = true;
    material.mDiffuseColor = color;
    entity.addComponent(pointLight);
    entity.addComponent(transform);
    entity.addComponent(mesh);
    entity.addComponent(material);
    return entity;
}

EntityHandle EntityFactory::createSpotlight(const std::string &name, const am::Vec3 &pos, const am::Vec3 &dir, const am::Vec3 &color)
{
    // Consists of: Spotlight, Transform
    static int lightInstance{0};
    auto entity = mWorld.createEntity(name);
    SpotlightComponent spotlight(lightInstance++, dir, color);
    spotlight.mShader = mDefaultShader;
    TransformComponent transform;
    transform.mPosition = pos;
    MeshComponent mesh{mMeshFactory.createSphere()};
    MaterialComponent material;
    material.mIsLight = true;
    material.mDiffuseColor = color;
    entity.addComponent(spotlight);
    entity.addComponent(transform);
    entity.addComponent(mesh);
    entity.addComponent(material);
    return entity;
}

EntityHandle EntityFactory::createCube(const std::string &name, const am::Vec3 &color, const am::Vec3 &pos)
{
    // Consists of: Mesh, Material, Transform
    auto entity = mWorld.createEntity(name);
    MeshComponent mesh{mMeshFactory.createCube()};
    MaterialComponent material;
    material.mDiffuseColor = color;
    material.mTextures.push_back(mMaterialFactory.getDiffuseTexture("inn"));
//    material.mTextures.push_back(mMaterialFactory.getEmissionTexture("innSpec"));
//    material.mTextures.push_back(mMaterialFactory.getSpecularTexture("innSpec"));
    TransformComponent transform;
    transform.mPosition = pos;
    entity.addComponent(mesh);
    entity.addComponent(material);
    entity.addComponent(transform);
    return entity;
}

EntityHandle EntityFactory::createSphere(const std::string &name, const am::Vec3 &color, const am::Vec3 &pos)
{
    // Consists of: Mesh, Material, Transform
    auto entity = mWorld.createEntity(name);
    MeshComponent mesh{mMeshFactory.createSphere()};
    MaterialComponent material;
    material.mDiffuseColor = color;
    TransformComponent transform;
    transform.mPosition = pos;
    entity.addComponent(mesh);
    entity.addComponent(material);
    entity.addComponent(transform);
    return entity;
}

EntityHandle EntityFactory::createModel(const std::string &name, const std::string &path, const am::Vec3 &pos)
{
    // Consists of: Mesh, Material, Transform
    auto entity = mWorld.createEntity(name);
    ModelComponent model{mMeshFactory.createModel(path)};
    TransformComponent transform;
    transform.mPosition = pos;
    MaterialComponent material;
    material.mHasDiffMap = true;
    material.mHasSpecMap = true;
    entity.addComponent(model);
    entity.addComponent(transform);
    entity.addComponent(material);
    return entity;
}

EntityHandle EntityFactory::createPlayerCube(const std::string &name, const am::Vec3 &color, const am::Vec3 &pos)
{
    // Consists of: Mesh, Material, Transform, Movement, Input
    auto entity = mWorld.createEntity(name);
    MeshComponent mesh{mMeshFactory.createCube()};
    MaterialComponent material;
    material.mDiffuseColor = color;
    material.mTextures.push_back(mMaterialFactory.getDiffuseTexture("kermit"));
    TransformComponent transform;
    transform.mPosition = pos;
    MovementComponent movement;
    InputComponent input(&mEngine.mViewport->mInputState);
    entity.addComponent(mesh);
    entity.addComponent(material);
    entity.addComponent(transform);
    entity.addComponent(movement);
    entity.addComponent(input);
    return entity;
}

EntityHandle EntityFactory::createPlayerSphere(const std::string &name, const am::Vec3 &color, const am::Vec3 &pos)
{
    // Consists of: Mesh, Material, Transform, Movement, Input
    auto entity = mWorld.createEntity(name);
    MeshComponent mesh{mMeshFactory.createSphere()};
    MaterialComponent material;
    material.mDiffuseColor = color;
//    material.mTextures.push_back(mMaterialFactory.getDiffuseTexture("container"));
    TransformComponent transform;
    transform.mPosition = pos;
    MovementComponent movement;
    InputComponent input(&mEngine.mViewport->mInputState);
    entity.addComponent(mesh);
    entity.addComponent(material);
    entity.addComponent(transform);
    entity.addComponent(movement);
    entity.addComponent(input);
    return entity;
}

EntityHandle EntityFactory::createFreeCamera(const std::string &name, const am::Vec3 &pos)
{
    // Consists of: Transform, Movement, Input, Camera, FreeCamera
    auto entity = mWorld.createEntity(name);
    TransformComponent transform;
    transform.mPosition = pos;
    transform.mEulerAngles.yaw() = -90.0f;
    MovementComponent movement;
    InputComponent input(&mEngine.mViewport->mInputState);
    CameraComponent camera(mDefaultShader);
    FreeCameraComponent freeCamera;
    entity.addComponent(transform);
    entity.addComponent(movement);
    entity.addComponent(input);
    entity.addComponent(camera);
    entity.addComponent(freeCamera);
    return entity;
}

EntityHandle EntityFactory::createMathTerrain(const std::string &name, const am::Vec3 &color, int min, int max, const am::Vec3 &pos)
{
    // TODO snakk med ole, constuctor i struct?
    // Consists of: Transform, Mesh, Material, Terrain
    MathTerrainGenerator terrainGen{min, max, 0.1f};
    auto entity = mWorld.createEntity(name);
    TransformComponent transform;
    transform.mPosition = pos;
    MeshComponent mesh{mMeshFactory.createTerrain(std::to_string(-min * max), terrainGen.mVertices, terrainGen.mIndices)};
    MaterialComponent material;
    material.mDiffuseColor = color;
    material.mTextures.push_back(mMaterialFactory.getDiffuseTexture("soilCrack"));
    TerrainComponent terrain;
    terrain.mTriangles = terrainGen.mTriangles;
    terrain.mVertices = terrainGen.mVertices;
    terrain.mIndices = terrainGen.mIndices;
    entity.addComponent(transform);
    entity.addComponent(mesh);
    entity.addComponent(material);
    entity.addComponent(terrain);
    return entity;
}

EntityHandle EntityFactory::createLasTerrain(const std::string &name, const am::Vec3 &color, const am::Vec3 &pos)
{
    // Consists of: Transform, Mesh, Material, Terrain
    LazTerrainGenerator terrainGen("data.las", 10.0f);
    auto entity = mWorld.createEntity(name);
    TransformComponent transform;
    transform.mPosition = pos;
    MeshComponent mesh{mMeshFactory.createTerrain(terrainGen.mPath, terrainGen.mVertices, terrainGen.mIndices)};
    MaterialComponent material;
    material.mDiffuseColor = color;
    TerrainComponent terrain;
    terrain.mVertices = terrainGen.mVertices;
    terrain.mIndices = terrainGen.mIndices;
    entity.addComponent(transform);
    entity.addComponent(mesh);
    entity.addComponent(material);
    entity.addComponent(terrain);
    return entity;
}

EntityHandle EntityFactory::createTestTriangle(const std::string &name, const am::Vec3 &color, const am::Vec3 &pos)
{
    auto entity = mWorld.createEntity(name);
    TransformComponent transform(pos);
    MaterialComponent material;
    material.mDiffuseColor = color;
    MeshComponent mesh = mMeshFactory.createTestTriangle();
    TerrainComponent terrain;
    std::vector<Vertex> vertices = {
        { am::Vec3{ 0.0f,  10.0f, -20.0f },   am::Vec3{ 0.0f, 0.707f, 0.707f },   am::Vec2{ 2.0f, 2.0f } },
        { am::Vec3{ -20.0f, 0.0f, 0.0f },	am::Vec3{ 0.0f, 1.0f, 0.0f },	am::Vec2{ 2.0f, 0.0f } },
        { am::Vec3{ 20.0f, 0.0f, 0.0f },   am::Vec3{ 0.0f, 1.0f, 0.0f },   am::Vec2{ 0.0f, 0.0f } },
        { am::Vec3{ 0.0f,  10.0f, 20.0f },	am::Vec3{ 0.0f, 0.707f, -0.707f },	am::Vec2{ 0.0f, 2.0f } }
    };
    std::vector<unsigned int> indices = { 0, 1, 2, 1, 3, 2 };
    terrain.mVertices = vertices;
    terrain.mIndices = indices;
    entity.addComponent(transform);
    entity.addComponent(material);
    entity.addComponent(mesh);
    entity.addComponent(terrain);
    return entity;
}

EntityHandle EntityFactory::createPhysicsBall(const std::string &name, const am::Vec3 &color, const am::Vec3 &pos)
{
    // Consists of: Mesh, Material, Transform, Movement, Input
    auto entity = mWorld.createEntity(name);
    MeshComponent mesh{mMeshFactory.createSphere()};
    MaterialComponent material;
    material.mTextures.push_back(mMaterialFactory.getDiffuseTexture("grass"));
    material.mDiffuseColor = color;
    TransformComponent transform;
    transform.mPosition = pos;
    MovementComponent movement;
    PhysicsComponent physics;
    entity.addComponent(mesh);
    entity.addComponent(material);
    entity.addComponent(transform);
    entity.addComponent(movement);
    entity.addComponent(physics);
    return entity;
}
