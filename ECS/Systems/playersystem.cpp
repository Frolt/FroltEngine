#include "playersystem.h"

playerSystem::playerSystem()
{
    mSystemMask.addComponent<InputComponent>();
    mSystemMask.addComponent<MovementComponent>();
    mSystemMask.addComponent<PlayerComponent>();
}

void playerSystem::beginPlay()
{

}

void playerSystem::update(float deltaTime)
{
    ch::Input input;
    ch::Movement movement;
    ch::Transform transform;
    for (auto entity : mRegisteredEntities) {
        mWorld->unpack(entity, input, movement, transform/*, camera*/);
        movePlayer(input, movement, deltaTime);
    }
}

void playerSystem::movePlayer(const InputComponent &input, MovementComponent &movement, float deltaTime) const
{
    float speed = 50.0f * deltaTime;
    float maxSpeed = 20.0f;

    if (input.keyPressed(Qt::Key_Up))
        movement.mVelocity.z = am::clamp(movement.mVelocity.z - speed, -maxSpeed, maxSpeed);
    if (input.keyPressed(Qt::Key_Left))
        movement.mVelocity.x = am::clamp(movement.mVelocity.x - speed, -maxSpeed, maxSpeed);
    if (input.keyPressed(Qt::Key_Down))
        movement.mVelocity.z = am::clamp(movement.mVelocity.z + speed, -maxSpeed, maxSpeed);
    if (input.keyPressed(Qt::Key_Right))
        movement.mVelocity.x = am::clamp(movement.mVelocity.x + speed, -maxSpeed, maxSpeed);

    // Friction
    movement.mVelocity *= 0.995f;
}
