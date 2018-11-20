#include "thirdpersoncamerasystem.h"
#include "engine.h"
#include "viewport.h"

ThirdPersonCameraSystem::ThirdPersonCameraSystem()
{
    mSystemMask.addComponent<TransformComponent>();
    mSystemMask.addComponent<ThirdPersonCameraComponent>();
}

void ThirdPersonCameraSystem::beginPlay()
{

}

void ThirdPersonCameraSystem::update(float deltaTime)
{
    ch::Transform transform;
    ch::ThirdPersonCamera camera;
    for (auto entity : mRegisteredEntities) {
        mWorld->unpack(entity, camera, transform);
        if (camera().mActive) {
            updateViewMatrixUniform(camera, transform, mWorld->getEntity(entity));
        }
    }
}

void ThirdPersonCameraSystem::updateViewMatrixUniform(const ThirdPersonCameraComponent &camera, const TransformComponent &transform, EntityHandle entity)
{
    auto cameraLocation = entity.getWorldLocation() + camera.mCameraRelativeLocation;
    auto view = am::Mat4::lookAt(cameraLocation, entity.getWorldLocation() + am::Vec3(0.0f, camera.mEyeHeight, 0.0f), am::up());
    auto projection = am::Mat4::perspective(am::toRadians(45.0f), mWorld->mEngine.mViewport->mAspect, 0.1f, 1000.0f);
    camera.mShader.setMat4("projection", projection);
    camera.mShader.setMat4("view", view);
    camera.mShader.setVec3("camPos", cameraLocation);
}
