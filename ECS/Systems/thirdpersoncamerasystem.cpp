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

    // Set camera rotation
    camera.mRotation.yaw += xOffset;
    camera.mRotation.pitch += yOffset;
    camera.mRotation.yaw = am::mod(transform.mRotation.yaw, 360.0f);
    camera.mRotation.pitch = am::clamp(transform.mRotation.pitch, -89.0f, 89.0f);
    transform.mRotation.yaw += xOffset;
    qDebug() << camera.mRotation;
}

void ThirdPersonCameraSystem::updateViewMatrixUniform(const ThirdPersonCameraComponent &camera, const TransformComponent &transform, EntityHandle entity)
{
    am::Mat4 cameraTransform;
    cameraTransform *= entity.getModelMatrix();
    cameraTransform.rotate(camera.mRotation.pitch, am::right());
    cameraTransform.translate(camera.mCameraRelativeLocation);
    am::Vec3 cameraLocation(cameraTransform(0,3), cameraTransform(1,3), cameraTransform(2,3));

    auto view = am::Mat4::lookAt(cameraLocation, entity.getWorldLocation() + am::Vec3(0.0f, camera.mEyeHeight, 0.0f), am::up());
    auto projection = am::Mat4::perspective(am::toRadians(45.0f), mWorld->mEngine.mViewport->mAspect, 0.1f, 1000.0f);
    camera.mShader.setMat4("projection", projection);
    camera.mShader.setMat4("view", view);
    camera.mShader.setVec3("camPos", cameraLocation);
}