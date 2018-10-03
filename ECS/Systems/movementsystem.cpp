#include "movementsystem.h"
#include <QDebug>
#include "ECS/Handles/componenthandle.h"
#include "ECS/Components/movement_component.h"
#include "ECS/Components/transform_component.h"
#include "world.h"

MovementSystem::MovementSystem()
{
    mSystemMask.addComponent<TransformComponent>();
    mSystemMask.addComponent<MovementComponent>();
}

void MovementSystem::beginPlay()
{

}

void MovementSystem::update(float deltaTime)
{
    for (auto &entity : mRegisteredEntities) {
        ComponentHandle<TransformComponent> transform;
        ComponentHandle<MovementComponent> movement;
        mWorld->unpack(entity, transform, movement);

        transform().mPosition += movement().mVelocity * deltaTime;
        movement().mVelocity += movement().mAcceleration * deltaTime;
    }
}
