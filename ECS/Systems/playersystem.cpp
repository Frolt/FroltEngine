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
    for (auto entity : mRegisteredEntities) {
        ComponentHandle<InputComponent> input;
        ComponentHandle<MovementComponent> movement;
        mWorld->unpack(entity, input, movement);
        processInput(input(), movement(), deltaTime);
    }
}

void playerSystem::processInput(const InputComponent &input, MovementComponent &movement, float deltaTime)
{
    if (input.keyPressed(Qt::Key_Up)) {
        movement.mVelocity.z -= 10.0f * deltaTime;
    }
    if (input.keyPressed(Qt::Key_Left)) {
        movement.mVelocity.x -= 10.0f * deltaTime;
    }
    if (input.keyPressed(Qt::Key_Down)) {
        movement.mVelocity.z += 10.0f * deltaTime;
    }
    if (input.keyPressed(Qt::Key_Right)) {
        movement.mVelocity.x += 10.0f * deltaTime;
    }
}
