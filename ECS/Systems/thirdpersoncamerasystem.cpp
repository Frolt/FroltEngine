#include "thirdpersoncamerasystem.h"
#include "engine.h"
#include "viewport.h"

ThirdPersonCameraSystem::ThirdPersonCameraSystem()
{
    mSystemMask.addComponent<TransformComponent>();
    mSystemMask.addComponent<ThirdPersonCameraComponent>();
    mSystemMask.addComponent<InputComponent>();
}

void ThirdPersonCameraSystem::beginPlay()
{

}

void ThirdPersonCameraSystem::update(float deltaTime)
{
    ch::Transform transform;
    ch::ThirdPersonCamera camera;
    ch::Input input;
    for (auto entity : mRegisteredEntities) {
        mWorld->unpack(entity, camera, transform, input);
        if (camera().mActive) {
            processMouse(input, transform, camera);
            updateViewMatrixUniform(camera, transform, mWorld->getEntity(entity));
        }

        mWorld->unpack(mWorld->getEntity("cube0"), transform);
        transform().mRotation.yaw += 0.5f;
        transform().mRotation.pitch += 0.5f;
        mWorld->unpack(mWorld->getEntity("cube1"), transform);
        transform().mRotation.yaw += 0.5f;
    }
}

void ThirdPersonCameraSystem::processMouse(const InputComponent &input, TransformComponent &transform, ThirdPersonCameraComponent &camera)
{
    // Find camera rotation
    static float mLastX{0.0f};
    static float mLastY{0.0f};
    auto xPos = static_cast<float>(input.mousePos().x);
    auto yPos = static_cast<float>(input.mousePos().y);
    float xOffset = xPos - mLastX;
    float yOffset = mLastY - yPos;
    mLastX = xPos;
    mLastY = yPos;

    // Mouse sense
    xOffset *= 0.2f;
    yOffset *= 0.2f;

    // Set player rotation

    // Set camera rotation
    camera.mRotation.yaw += xOffset;
    camera.mRotation.pitch += yOffset;
    camera.mRotation.yaw = am::mod(camera.mRotation.yaw, 360.0f);
    // TODO fix pitch clamp
    camera.mRotation.pitch = am::clampLength(camera.mRotation.pitch, -50.0f, 89.0f);
    qDebug() << camera.mRotation.pitch;
}

void ThirdPersonCameraSystem::updateViewMatrixUniform(const ThirdPersonCameraComponent &camera, const TransformComponent &transform, EntityHandle entity)
{
//    entity.setRelativeRotation(-camera.mRotation.yaw, 0.0f, 0.0f);

    am::Mat4 cameraTransform;
    cameraTransform.translate(entity.getWorldLocation());
    cameraTransform.rotate(-camera.mRotation.yaw, am::up());
    cameraTransform.rotate(-camera.mRotation.pitch, am::forward());
    cameraTransform.translate(camera.mCameraRelativeLocation);
    am::Vec3 cameraLocation(cameraTransform(0,3), cameraTransform(1,3), cameraTransform(2,3));

    auto view = am::Mat4::lookAt(cameraLocation, entity.getWorldLocation() + am::Vec3(0.0f, camera.mEyeHeight, 0.0f), am::up());
    auto projection = am::Mat4::perspective(am::toRadians(45.0f), mWorld->mEngine.mViewport->mAspect, 0.1f, 1000.0f);
    camera.mShader.setMat4("projection", projection);
    camera.mShader.setMat4("view", view);
    camera.mShader.setVec3("camPos", cameraLocation);
}
