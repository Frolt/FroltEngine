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

#include "world.h"

class System
{
public:
    System() = default;
    virtual ~System();
    virtual void beginPlay();
    virtual void update(float deltaTime);

    void setWorld(World *world);
    void registerEntity(const Entity &entity);
    void deRegisterEntity(const Entity &entity);

public:
    ComponentMask mSystemMask;
protected:
    // TODO vector has slow search O(n)
    // bad when ComponentMask uses deRegisterEntity() method
    // but vector is good for iterating
    std::vector<Entity> mRegisteredEntities;
    World *mWorld;
};

#endif // SYSTEM_H
