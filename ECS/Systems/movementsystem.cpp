#include "movementsystem.h"
#include <QDebug>
#include "ECS/Handles/componenthandle.h"
#include "ECS/Components/movementcomponent.h"
#include "ECS/Components/transformcomponent.h"
#include "world.h"

MovementSystem::MovementSystem()
{
    mSystemMask.addComponent<TransformComponent>();
    mSystemMask.addComponent<MovementComponent>();
}

void MovementSystem::beginPlay()
{
    qDebug() << "MovementSystem init()";
}

void MovementSystem::update(float deltaTime)
{
    for (auto &entity : mRegisteredEntities) {
        qDebug() << "MovementSystem update()";
      ComponentHandle<TransformComponent> transform;
      ComponentHandle<MovementComponent> movement;
      mWorld->unpack(entity, transform, movement);

      transform().mPosition += movement().mVelocity * deltaTime;
      movement().mVelocity += movement().mAcceleration * deltaTime;
    }
}
