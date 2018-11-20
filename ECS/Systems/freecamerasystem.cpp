#include "freecamerasystem.h"
#include "engine.h"
#include "viewport.h"

FreeCameraSystem::FreeCameraSystem()
{
    mSystemMask.addComponent<TransformComponent>();
    mSystemMask.addComponent<FreeCameraComponent>();
    mSystemMask.addComponent<InputComponent>();
    mSystemMask.addComponent<MovementComponent>();
}

void FreeCameraSystem::beginPlay()
{

}

void FreeCameraSystem::update(float)
{

    ch::Transform transform;
    ch::FreeCamera camera;
    ch::Input input;
    ch::Movement movement;
    for (auto &entity : mRegisteredEntities) {
        mWorld->unpack(entity, transform, camera, input, movement);
        // Eject/possess pawn
        // -----------------------------------------------------------
        static bool canPossess{true};
        static bool isPossessingPlayer{true};
        if (input().keyPressed(Qt::Key_F8) && canPossess) {
            if (isPossessingPlayer) {
                mWorld->activateCamera(mWorld->getEntity("camera"));
                isPossessingPlayer = false;
                canPossess = false;
            } else {
                mWorld->activateCamera(mWorld->getEntity("player"));
                isPossessingPlayer = true;
                canPossess = false;
            }
        } else if (!input().keyPressed(Qt::Key_F8)){
            canPossess = true;
        }
        // -----------------------------------------------------------
        if (camera().mActive) {
            processKeyboard(input, movement, camera);
            processMouse(input, camera, transform);
            processScroll(camera, input);
            updateCameraVectors(transform, camera);
            updateUniforms(transform, camera, mWorld->getEntity(entity));
        }
    }
}

void FreeCameraSystem::processKeyboard(const InputComponent &input, MovementComponent &movement, FreeCameraComponent &freeCamera) const
{
    am::Vec vel;

    // Camera movement
    if (input.keyPressed(Qt::Key_W))
        vel += freeCamera.mFront * freeCamera.mMoveSpeed;
    if (input.keyPressed(Qt::Key_A))
        vel -= freeCamera.mRight * freeCamera.mMoveSpeed;
    if (input.keyPressed(Qt::Key_S))
        vel -= freeCamera.mFront * freeCamera.mMoveSpeed;
    if (input.keyPressed(Qt::Key_D))
        vel += freeCamera.mRight * freeCamera.mMoveSpeed;
    if (input.keyPressed(Qt::Key_Space))
        vel += freeCamera.mWorldUp * freeCamera.mMoveSpeed;
    if (input.keyPressed(Qt::Key_Control))
        vel -= freeCamera.mWorldUp * freeCamera.mMoveSpeed;
    movement.mVelocity = vel;

    // Zoom
    static bool canZoom{true};
    if (input.keyPressed(Qt::Key_Plus) && canZoom) {
        freeCamera.mZoom -= freeCamera.mZoomStr;
        canZoom = false;
    } else if (input.keyPressed(Qt::Key_Minus) && canZoom) {
        freeCamera.mZoom += freeCamera.mZoomStr;
        canZoom = false;
    } else if (!input.keyPressed(Qt::Key_Plus) && !input.keyPressed(Qt::Key_Minus)) {
        canZoom = true;
    }
    freeCamera.mZoom = am::clamp(freeCamera.mZoom, 10.0f, 45.0f);
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

        transform.mRotation.yaw += xOffset;
        transform.mRotation.pitch += yOffset;
        transform.mRotation.yaw = am::mod(transform.mRotation.yaw, 360.0f);
        transform.mRotation.pitch = am::clamp(transform.mRotation.pitch, -89.0f, 89.0f);
    }
}

void FreeCameraSystem::processScroll(FreeCameraComponent &freeCamera, const InputComponent &input) const
{
    static int lastWheelPos{input.wheelAngleDelta().y()};
    int currentWheelPos = input.wheelAngleDelta().y();
    float scrollDelta = static_cast<float>(currentWheelPos - lastWheelPos);

    if (input.keyPressed(Qt::Key_Shift)) {
        // Zoom
        auto str = scrollDelta / 120.0f * freeCamera.mZoomStr;
        freeCamera.mZoom -= str;
        freeCamera.mZoom = am::clamp(freeCamera.mZoom, 10.0f, 45.0f);
    } else {
        // Camera speed
        freeCamera.mMoveSpeed += (scrollDelta / 120.0f) * freeCamera.mMoveStr;
        freeCamera.mMoveSpeed = am::clamp(freeCamera.mMoveSpeed, 10.0f, 1000.0f);
    }


    lastWheelPos = currentWheelPos;
}

void FreeCameraSystem::updateCameraVectors(const TransformComponent &transform, FreeCameraComponent &freeCamera) const
{
    am::Vec front;
    front.x = cos(am::toRadians(transform.mRotation.yaw)) * cos(am::toRadians(transform.mRotation.pitch));
    front.y = sin(am::toRadians(transform.mRotation.pitch));
    front.z = sin(am::toRadians(transform.mRotation.yaw)) * cos(am::toRadians(transform.mRotation.pitch));
    freeCamera.mFront = am::normalize(front);

    freeCamera.mRight = am::normalize(am::cross(freeCamera.mFront, freeCamera.mWorldUp));
    freeCamera.mUp = -am::normalize(am::cross(freeCamera.mFront, freeCamera.mRight));
}

void FreeCameraSystem::updateUniforms(const TransformComponent &transform, const FreeCameraComponent &camera, EntityHandle entity) const
{
    auto view = am::Mat4::lookAt(entity.getWorldLocation(), entity.getWorldLocation() + camera.mFront, camera.mWorldUp);
    auto projection = am::Mat4::perspective(am::toRadians(camera.mZoom), mWorld->mEngine.mViewport->mAspect, 0.1f, 1000.0f);
    camera.mShader.setMat4("projection", projection);
    camera.mShader.setMat4("view", view);
    camera.mShader.setVec3("camPos", entity.getWorldLocation());
}
