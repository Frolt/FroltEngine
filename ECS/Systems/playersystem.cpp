#include "playersystem.h"

playerSystem::playerSystem()
{
    mSystemMask.addComponent<InputComponent>();
    mSystemMask.addComponent<MovementComponent>();
}

void playerSystem::beginPlay()
{

}

void playerSystem::update(float deltaTime)
{
    ch::Input input;
    ch::Movement movement;
    for (auto &entity : mRegisteredEntities) {
        mWorld->unpack(entity, input, movement);
        processInput(input, movement, deltaTime);
    }
}

void playerSystem::processInput(const InputComponent &input, MovementComponent &movement, float deltaTime) const
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
