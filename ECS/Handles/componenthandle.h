#ifndef COMPONENTHANDLE_H
#define COMPONENTHANDLE_H

#include "ECS/entity.h"


// Forward declarations
template<typename ComponentType>
class ComponentManager;
class World;
struct TransformComponent;
struct PhysicsComponent;
struct DirectionalLightComponent;
struct FreeCameraComponent;
struct ThirdPersonCameraComponent;
struct InputComponent;
struct MaterialComponent;
struct MeshComponent;
struct ModelComponent;
struct MovementComponent;
struct PointLightComponent;
struct SpotlightComponent;
struct TerrainComponent;
struct BSplineComponent;
struct CollisionComponent;
struct SkyboxComponent;
struct AiComponent;
struct PlayerComponent;

template<typename ComponentType>
/**
   @brief The ComponentHandle struct
 */
struct ComponentHandle
{
    ComponentHandle() = default;
    ComponentHandle(World *world, EntityID owner);
    void destroy();
    /// Overloads the parentheses to return the component reference
    ComponentType &operator()();
    /// Overloads the parentheses to return the const component reference
    const ComponentType &operator()() const;
    /// Provides implicit casting to a component type
    operator ComponentType &();

public:
    ComponentType *mComponent{nullptr};
private:
    World *mWorld{nullptr};
    EntityID mOwner;
};

/// Provides handy type-shortcuts for all the different ComponentHandles<T>
namespace ch {
    using Transform = ComponentHandle<TransformComponent>;
    using Physics = ComponentHandle<PhysicsComponent>;
    using DirLight = ComponentHandle<DirectionalLightComponent>;
    using ThirdPersonCamera = ComponentHandle<ThirdPersonCameraComponent>;
    using FreeCamera = ComponentHandle<FreeCameraComponent>;
    using Input = ComponentHandle<InputComponent>;
    using Material = ComponentHandle<MaterialComponent>;
    using Mesh = ComponentHandle<MeshComponent>;
    using Model = ComponentHandle<ModelComponent>;
    using Movement = ComponentHandle<MovementComponent>;
    using PointLight = ComponentHandle<PointLightComponent>;
    using Spotlight = ComponentHandle<SpotlightComponent>;
    using Terrain = ComponentHandle<TerrainComponent>;
    using BSpline = ComponentHandle<BSplineComponent>;
    using Collision = ComponentHandle<CollisionComponent>;
    using Skybox = ComponentHandle<SkyboxComponent>;
    using Ai = ComponentHandle<AiComponent>;
    using Player = ComponentHandle<PlayerComponent>;
}

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

#include "ECS/Managers/componentmanager.h"
#include "world.h"

template<typename ComponentType>
ComponentHandle<ComponentType>::ComponentHandle(World *world, EntityID owner)
    : mWorld{world}, mOwner{owner}
{
    mComponent = mWorld->getComponent<ComponentType>(owner);
}

template<typename ComponentType>
void ComponentHandle<ComponentType>::destroy()
{
    mWorld->removeComponent<ComponentType>(mOwner);
}

template<typename ComponentType>
ComponentType &ComponentHandle<ComponentType>::operator()()
{
    return *mComponent;
}

template<typename ComponentType>
const ComponentType &ComponentHandle<ComponentType>::operator()() const
{
    return *mComponent;
}

template<typename ComponentType>
ComponentHandle<ComponentType>::operator ComponentType &()
{
    return *mComponent;
}

#endif // COMPONENTHANDLE_H
