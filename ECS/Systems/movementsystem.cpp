#include "movementsystem.h"
#include <QDebug>
#include "ECS/Handles/componenthandle.h"
#include "ECS/Components/movementcomponent.h"
#include "ECS/Components/transformcomponent.h"
#include "world.h"

MovementSystem::MovementSystem()
{
    mSystemSignature.set(3);
    mSystemSignature.set(18);
}

void MovementSystem::beginPlay()
{
    qDebug() << "MovementSystem init()";
}

void MovementSystem::update(float deltaTime)
{
    for (auto &entity : mRegisteredEntities) {
      ComponentHandle<TransformComponent> transform;
      ComponentHandle<MovementComponent> movement;
      mWorld->unpack(entity, transform, movement);

      transform.mComponent->mPosition += movement.mComponent->mVelocity * deltaTime;
      movement.mComponent->mVelocity += movement.mComponent->mAcceleration * deltaTime;
    }
}
