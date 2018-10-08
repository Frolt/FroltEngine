#include "movementsystem.h"

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
