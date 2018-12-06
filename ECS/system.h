#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <bitset>
#include <QDebug>
#include "entity.h"
#include "ECS/Handles/entityhandle.h"
#include "ECS/Handles/componenthandle.h"
#include "ECS/component_mask.h"
#include "ECS/Components/input_component.h"
#include "ECS/Components/transform_component.h"
#include "ECS/Components/directionallight_component.h"
#include "ECS/Components/spotlight_component.h"
#include "ECS/Components/pointlight_component.h"
#include "ECS/Components/movement_component.h"
#include "ECS/Components/mesh_component.h"
#include "ECS/Components/material_component.h"
#include "ECS/Components/camera_component.h"
#include "ECS/Components/free_camera_component.h"
#include "ECS/Components/terrain_component.h"
#include "ECS/Components/model_component.h"
#include "ECS/Components/physics_component.h"
#include "ECS/Components/bspline_component.h"
#include "ECS/Components/collision_component.h"
#include "ECS/Components/player_component.h"
#include "ECS/Components/ai_component.h"
#include "ECS/Components/third_person_camera_component.h"
#include "ECS/Components/skybox_component.h"
#include "world.h"
#include "EventSystem/event.h"
#include "EventSystem/eventhandler.h"
#include "EventSystem/collisionevent.h"
#include "EventSystem/spherecollisionevent.h"


// Forward declarations
class World;
class EventHandler;

/**
   @brief The System class is an interface class for all systems.
    It stores a World and EventHandler reference aswell as a list of entity IDs that the system care about
 */
class System
{
public:
    virtual ~System() = default;
    virtual void beginPlay();
    virtual void update(float deltaTime);

    void setWorld(World *world);
    void setEventHandler(EventHandler *eventHandler);
    /// add an entity the system should pay attention to
    void registerEntity(EntityID entity);
    /// remove an entity the system should no longer pay attention to
    void deRegisterEntity(EntityID entity);

public:
    /// Represents the components that an entity should have for the system to pay attention to it
    ComponentMask mSystemMask;
protected:
    /// Reference to all entities that match the systemMask
    std::vector<EntityID> mRegisteredEntities;
    World *mWorld;
    EventHandler *mEventHandler;
};

#endif // SYSTEM_H
