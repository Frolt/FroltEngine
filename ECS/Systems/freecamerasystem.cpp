#include "freecamerasystem.h"

FreeCameraSystem::FreeCameraSystem()
{
    mSystemMask.addComponent<TransformComponent>();
    mSystemMask.addComponent<CameraComponent>();
    mSystemMask.addComponent<FreeCameraComponent>();
    mSystemMask.addComponent<InputComponent>();
    mSystemMask.addComponent<MovementComponent>();
}

void FreeCameraSystem::beginPlay()
{
    ch::Transform transform;
    ch::FreeCamera freeCamera;
    for (auto entity : mRegisteredEntities) {
        mWorld->unpack(entity, transform, freeCamera);
        updateCameraVectors(transform(), freeCamera());
    }
}

void FreeCameraSystem::update(float)
{
    ch::Transform transform;
    ch::Camera camera;
    ch::FreeCamera freeCamera;
    ch::Input input;
    ch::Movement movement;
    for (auto entity : mRegisteredEntities) {
        mWorld->unpack(entity, transform, camera, freeCamera, input, movement);
        processKeyboard(input, movement, freeCamera);
        processMouse(input, freeCamera, transform);
        processScroll(freeCamera, input);
        updateCameraVectors(transform, freeCamera);
        updateUniforms(transform, freeCamera, camera);
    }
}

void FreeCameraSystem::processKeyboard(const InputComponent &input, MovementComponent &movement, const FreeCameraComponent &freeCamera) const
{
    movement.mVelocity = am::zero();
    am::Vec tempVel;

    if (input.keyPressed(Qt::Key_W))
        tempVel += freeCamera.mFront * freeCamera.mMoveSpeed;
    if (input.keyPressed(Qt::Key_A))
        tempVel -= freeCamera.mRight * freeCamera.mMoveSpeed;
    if (input.keyPressed(Qt::Key_S))
        tempVel -= freeCamera.mFront * freeCamera.mMoveSpeed;
    if (input.keyPressed(Qt::Key_D))
        tempVel += freeCamera.mRight * freeCamera.mMoveSpeed;
    if (input.keyPressed(Qt::Key_Space))
        tempVel += freeCamera.mWorldUp * freeCamera.mMoveSpeed;
    if (input.keyPressed(Qt::Key_Control))
        tempVel -= freeCamera.mWorldUp * freeCamera.mMoveSpeed;

    movement.mVelocity = tempVel;
}

void FreeCameraSystem::processMouse(const InputComponent &input, const FreeCameraComponent &freeCamera, TransformComponent &transform) const
{
    // in renderwindow
    // FIND CAMERA ROTATION VALUES
    static float mLastX{0.0f};
    static float mLastY{0.0f};
    auto xPos = static_cast<float>(input.mousePos().x);
    auto yPos = static_cast<float>(input.mousePos().y);
    float xOffset = xPos - mLastX;
    float yOffset = mLastY - yPos;
    mLastX = xPos;
    mLastY = yPos;

    if (input.mousePressed(Qt::RightButton)) {
        // in camera.cpp
        xOffset *= freeCamera.mMouseSense;
        yOffset *= freeCamera.mMouseSense;

        transform.mEulerAngles.yaw() += xOffset;
        transform.mEulerAngles.pitch() += yOffset;
        transform.mEulerAngles.yaw() = am::mod(transform.mEulerAngles.yaw(), 360.0f);
        transform.mEulerAngles.pitch() = am::clamp(transform.mEulerAngles.pitch(), -89.0f, 89.0f);
    }
}

void FreeCameraSystem::processScroll(FreeCameraComponent &freeCamera, const InputComponent &input) const
{
    static int lastWheelPos{0};
    int currentWheelPos = input.wheelAngleDelta().y();
    float scrollDelta = static_cast<float>(currentWheelPos - lastWheelPos);
    freeCamera.mMoveSpeed += (scrollDelta / 120.0f) * freeCamera.mMoveStr;
    freeCamera.mMoveSpeed = am::clamp(freeCamera.mMoveSpeed, 10.0f, 1000.0f);
    lastWheelPos = currentWheelPos;
}

void FreeCameraSystem::updateCameraVectors(const TransformComponent &transform, FreeCameraComponent &freeCamera) const
{
    am::Vec front;
    front.x = cos(am::toRadians(transform.mEulerAngles.yaw())) * cos(am::toRadians(transform.mEulerAngles.pitch()));
    front.y = sin(am::toRadians(transform.mEulerAngles.pitch()));
    front.z = sin(am::toRadians(transform.mEulerAngles.yaw())) * cos(am::toRadians(transform.mEulerAngles.pitch()));
    freeCamera.mFront = am::normalize(front);

    freeCamera.mRight = am::normalize(am::cross(freeCamera.mFront, freeCamera.mWorldUp));
    freeCamera.mUp = -am::normalize(am::cross(freeCamera.mFront, freeCamera.mRight));
}

void FreeCameraSystem::updateUniforms(const TransformComponent &transform, const FreeCameraComponent &freeCamera, const CameraComponent &camera) const
{
    auto view = am::Mat4::lookAt(transform.mPosition, transform.mPosition + freeCamera.mFront, freeCamera.mWorldUp);
//    auto projection = am::Mat4::perspective(am::toRadians(freeCamera.mZoom), freeCamera.mAspect, 0.1f, 1000.0f);
//    camera.mShader.setMat4("projection", projection);
    camera.mShader.setMat4("view", view);
    camera.mShader.setVec3("camPos", transform.mPosition);

}
