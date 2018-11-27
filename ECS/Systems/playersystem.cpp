#include "playersystem.h"
#include "engine.h"

PlayerSystem::PlayerSystem()
{
    mSystemMask.addComponent<InputComponent>();
    mSystemMask.addComponent<MovementComponent>();
    mSystemMask.addComponent<PlayerComponent>();
}

void PlayerSystem::beginPlay()
{

}

void PlayerSystem::update(float deltaTime)
{
    ch::Input input;
    ch::Movement movement;
    ch::Transform transform;
    ch::ThirdPersonCamera camera;
    for (auto entity : mRegisteredEntities) {
        mWorld->unpack(entity, input, movement, transform, camera);
        if (camera().mActive) {
            movePlayer(input, movement, deltaTime, mWorld->getEntity(entity));
        }
    }
}

void PlayerSystem::movePlayer(const InputComponent &input, MovementComponent &movement, float deltaTime, EntityHandle entity) const
{
    float speed = 50.0f * deltaTime;
    float maxSpeed = 20.0f;

    if (input.keyPressed(Qt::Key_W))
        movement.mVelocity += entity.getForwardVector() * speed;
    if (input.keyPressed(Qt::Key_A))
        movement.mVelocity -= entity.getRightVector() * speed;
    if (input.keyPressed(Qt::Key_S))
        movement.mVelocity -= entity.getForwardVector() * speed;
    if (input.keyPressed(Qt::Key_D))
        movement.mVelocity += entity.getRightVector() * speed;

    float jumpTimer{0.5f};
    static float timeSinceJump{0.0f};
    if (mWorld->mEngine.getTime() - timeSinceJump > jumpTimer && input.keyPressed(Qt::Key_Space)) {
        timeSinceJump = mWorld->mEngine.getTime();
        movement.mVelocity.y = 0.0f;
        movement.mVelocity += am::up() * 50.0f;
    }
//    movement.mVelocity = am::clampLength(movement.mVelocity, -maxSpeed, maxSpeed);

    // Friction
    movement.mVelocity *= 0.995f;
}
