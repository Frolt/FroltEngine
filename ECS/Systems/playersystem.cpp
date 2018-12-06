#include "playersystem.h"
#include "engine.h"
#include "entityfactory.h"


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
    ch::Player player;
    for (auto entity : mRegisteredEntities) {
        mWorld->unpack(entity, input, movement, transform, camera, player);
        if (camera().mActive && !player().isDead) {
            movePlayer(input, transform, movement, deltaTime, mWorld->getEntity(entity));
        }
    }
}

void PlayerSystem::movePlayer(const InputComponent &input, const TransformComponent &transform, MovementComponent &movement, float deltaTime, EntityHandle entity) const
{
    float speed = 50.0f * deltaTime;
    float maxSpeed = 20.0f;

    // Move
    if (input.keyPressed(Qt::Key_W))
        movement.mVelocity += entity.getForwardVector() * speed;
    if (input.keyPressed(Qt::Key_A))
        movement.mVelocity -= entity.getRightVector() * speed;
    if (input.keyPressed(Qt::Key_S))
        movement.mVelocity -= entity.getForwardVector() * speed;
    if (input.keyPressed(Qt::Key_D))
        movement.mVelocity += entity.getRightVector() * speed;

    // Jump
    float jumpTimer{0.5f};
    static float timeSinceJump{0.0f};
    if (mWorld->mEngine.getTime() - timeSinceJump > jumpTimer && input.keyPressed(Qt::Key_Space)) {
        timeSinceJump = mWorld->mEngine.getTime();
        movement.mVelocity.y = 0.0f;
        movement.mVelocity += am::up() * 30.0f;
    }
//    movement.mVelocity = am::clampLength(movement.mVelocity, -maxSpeed, maxSpeed);

    // Shoot
    float shootTimer{0.5f};
    static float timeSinceShoot{0.0f};
    if (input.mousePressed(Qt::MouseButton::LeftButton) && mWorld->mEngine.getTime() - timeSinceShoot > shootTimer) {
        timeSinceShoot = mWorld->mEngine.getTime();
        static int index{0};
        auto projectile = mWorld->mEngine.mEntityFactory->createModel("projectile" + std::to_string(index++), "Arrow.fbx", transform.mLocation + entity.getForwardVector() * 10.0f);
        MovementComponent movement;
        CollisionComponent collision;
        projectile.addComponent(collision);
        projectile.addComponent(PhysicsComponent());
        movement.mVelocity = entity.getForwardVector() * 100.0f;
        projectile.addComponent(movement);
        projectile.setRelativeRotation(transform.mRotation.yaw + 90.0f, 90.0f, 0.0f);
        projectile.setRelativeScale(4.0f, 4.0f, 4.0f);
        ch::Material material;
        mWorld->unpack(projectile, material);
        material().mHasDiffMap = false;
        material().mDiffuseColor = Color::red;
    }

    // Friction
    movement.mVelocity *= 0.999f;
}
