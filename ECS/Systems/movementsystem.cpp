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
    ch::Transform transform;
    ch::Movement movement;
    for (auto &entity : mRegisteredEntities) {
        mWorld->unpack(entity, transform, movement);

        transform().mLocation += movement().mVelocity * deltaTime;
        movement().mVelocity += movement().mAcceleration * deltaTime;
    }
}
