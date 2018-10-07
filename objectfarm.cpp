#include "objectfarm.h"
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
#include "meshfarm.h"
#include "world.h"
#include "octahedron.h"


ObjectFarm::ObjectFarm(MeshFarm &meshFarm, World &world, Shader &shader)
    : mMeshFarm{meshFarm}, mWorld{world}, mDefaultShader{shader}
{

}

EntityHandle ObjectFarm::createDirectionalLight(const std::string &name, const am::Vec3 &color)
{
    auto entity = mWorld.createEntity(name);
    DirectionalLightComponent dirLight(-am::up(), am::Vec{0.1}, am::Vec{1});
    dirLight.mShader = mDefaultShader;
    entity.addComponent(dirLight);
    return EntityHandle(&mWorld, entity());
}

EntityHandle ObjectFarm::createPointLight(const std::string &name, const am::Vec3 &pos, const am::Vec3 &color)
{
    auto entity = mWorld.createEntity(name);
    PointLightComponent pointLight{am::Vec{0.1}, am::Vec{1}};
    pointLight.mShader = mDefaultShader;
    TransformComponent transform;
    transform.mPosition = pos;
    entity.addComponent(transform);
    entity.addComponent(pointLight);
    return EntityHandle(&mWorld, entity());
}

EntityHandle ObjectFarm::createSpotlight(const std::string &name, const am::Vec3 &pos, const am::Vec3 &color)
{
    auto entity = mWorld.createEntity(name);
    SpotlightComponent spotlight(-am::forward(), am::Vec{0.1}, am::Vec{1});
    spotlight.mShader = mDefaultShader;
    TransformComponent transform;
    transform.mPosition = pos;
    entity.addComponent(transform);
    entity.addComponent(spotlight);
    return EntityHandle(&mWorld, entity());
}

EntityHandle ObjectFarm::createCube(const std::string &name, const am::Vec3 &color, const am::Vec3 &pos)
{
    auto entity = mWorld.createEntity(name);
    MeshComponent mesh = mMeshFarm.createCube();
    MaterialComponent material;
    material.mDiffuseColor = color;
    TransformComponent transform;
    transform.mPosition = pos;
    entity.addComponent(mesh);
    entity.addComponent(material);
    entity.addComponent(transform);
    return EntityHandle(&mWorld, entity());
}

EntityHandle ObjectFarm::createSphere(const std::string &name, const am::Vec3 &color, const am::Vec3 &pos)
{
    auto entity = mWorld.createEntity(name);
    MeshComponent mesh = mMeshFarm.createSphere();
    MaterialComponent material;
    material.mDiffuseColor = color;
    TransformComponent transform;
    transform.mPosition = pos;
    entity.addComponent(mesh);
    entity.addComponent(material);
    entity.addComponent(transform);
    return EntityHandle(&mWorld, entity());
}
