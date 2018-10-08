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
    for (auto entity : mRegisteredEntities) {
        ComponentHandle<TransformComponent> transform;
        ComponentHandle<FreeCameraComponent> freeCamera;
        mWorld->unpack(entity, transform, freeCamera);
        updateCameraVectors(transform(), freeCamera());
    }
}

void FreeCameraSystem::update(float deltaTime)
{
    for (auto entity : mRegisteredEntities) {
//        qDebug() << "freeCameraSystem update!";
        ComponentHandle<TransformComponent> transform;
        ComponentHandle<CameraComponent> camera;
        ComponentHandle<FreeCameraComponent> freeCamera;
        ComponentHandle<InputComponent> input;
        ComponentHandle<MovementComponent> movement;
        mWorld->unpack(entity, transform, camera, freeCamera, input, movement);
        processKeyboard(input(), movement(), freeCamera(), deltaTime);
        processMouse(input(), freeCamera(), transform());
        processScroll();
        updateCameraVectors(transform(), freeCamera());
        updateUniforms(transform(), freeCamera(), camera());
    }
}

void FreeCameraSystem::processKeyboard(InputComponent &input, MovementComponent &movement, FreeCameraComponent &freeCamera, float deltaTime)
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

void FreeCameraSystem::processMouse(InputComponent &input, FreeCameraComponent &freeCamera, TransformComponent &transform)
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

void FreeCameraSystem::processScroll()
{
    // TODO
}

void FreeCameraSystem::updateCameraVectors(TransformComponent &transform, FreeCameraComponent &freeCamera)
{
    am::Vec front;
    front.x = cos(am::toRadians(transform.mEulerAngles.yaw())) * cos(am::toRadians(transform.mEulerAngles.pitch()));
    front.y = sin(am::toRadians(transform.mEulerAngles.pitch()));
    front.z = sin(am::toRadians(transform.mEulerAngles.yaw())) * cos(am::toRadians(transform.mEulerAngles.pitch()));
    freeCamera.mFront = am::normalize(front);

    freeCamera.mRight = am::normalize(am::cross(freeCamera.mFront, freeCamera.mWorldUp));
    freeCamera.mUp = -am::normalize(am::cross(freeCamera.mFront, freeCamera.mRight));
}

void FreeCameraSystem::updateUniforms(TransformComponent &transform, FreeCameraComponent &freeCamera, CameraComponent &camera)
{
    auto view = am::Mat4::lookAt(transform.mPosition, transform.mPosition + freeCamera.mFront, freeCamera.mWorldUp);
    // TODO set projection matrix here
//    auto perspective = am::Mat4::perspective(am::toRadians(45.0f), mViewport->mAspect, 0.1f, 1000.0f);
//    camera.mShader.setMat4("projection", perspective);
    camera.mShader.setMat4("view", view);
    camera.mShader.setVec3("camPos", transform.mPosition);

}
