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
        if (camera().mActive) {
            processKeyboard(input, movement, camera, mWorld->getEntity(entity));
            processMouse(input, camera, transform);
            processScroll(camera, input);
            updateUniforms(camera, mWorld->getEntity(entity));
        }
    }
}

void FreeCameraSystem::processKeyboard(const InputComponent &input, MovementComponent &movement, FreeCameraComponent &freeCamera, EntityHandle entity) const
{
    am::Vec vel;

    // Camera movement
    if (input.keyPressed(Qt::Key_W))
        vel += entity.getForwardVector() * freeCamera.mMoveSpeed;
    if (input.keyPressed(Qt::Key_A))
        vel -= entity.getRightVector() * freeCamera.mMoveSpeed;
    if (input.keyPressed(Qt::Key_S))
        vel -= entity.getForwardVector() * freeCamera.mMoveSpeed;
    if (input.keyPressed(Qt::Key_D))
        vel += entity.getRightVector() * freeCamera.mMoveSpeed;
    if (input.keyPressed(Qt::Key_Space))
        vel += am::up() * freeCamera.mMoveSpeed;
    if (input.keyPressed(Qt::Key_Control))
        vel -= am::up() * freeCamera.mMoveSpeed;
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
    freeCamera.mZoom = am::clampLength(freeCamera.mZoom, 10.0f, 45.0f);
}

void FreeCameraSystem::processMouse(const InputComponent &input, const FreeCameraComponent &freeCamera, TransformComponent &transform) const
{
    // in renderwindow
    // FIND CAMERA ROTATION VALUES
    static float mLastX{0.0f};
    static float mLastY{0.0f};
    auto xPos = static_cast<float>(input.mousePos().x());
    auto yPos = static_cast<float>(input.mousePos().y());
    float xOffset = xPos - mLastX;
    float yOffset = mLastY - yPos;
    mLastX = xPos;
    mLastY = yPos;

    if (input.mousePressed(Qt::RightButton)) {
        // in camera.cpp
        xOffset *= freeCamera.mMouseSense;
        yOffset *= freeCamera.mMouseSense;

        transform.mRotation.yaw -= xOffset;
        transform.mRotation.pitch += yOffset;
        transform.mRotation.yaw = am::mod(transform.mRotation.yaw, 360.0f);
        transform.mRotation.pitch = am::clampLength(transform.mRotation.pitch, -89.0f, 89.0f);
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
        freeCamera.mZoom = am::clampLength(freeCamera.mZoom, 10.0f, 45.0f);
    } else {
        // Camera speed
        freeCamera.mMoveSpeed += (scrollDelta / 120.0f) * freeCamera.mMoveStr;
        freeCamera.mMoveSpeed = am::clampLength(freeCamera.mMoveSpeed, 10.0f, 1000.0f);
    }

    lastWheelPos = currentWheelPos;
}

void FreeCameraSystem::updateUniforms(const FreeCameraComponent &camera, EntityHandle entity) const
{
    auto view = am::Mat4::lookAt(entity.getWorldLocation(), entity.getWorldLocation() + entity.getForwardVector(), am::up());
    auto projection = am::Mat4::perspective(am::toRadians(camera.mZoom), mWorld->mEngine.mViewport->mAspect, 0.1f, 1000.0f);
    camera.mShader.setMat4("projection", projection);
    camera.mShader.setMat4("view", view);
    camera.mShader.setVec3("camPos", entity.getWorldLocation());

    // Set skybox shader uniforms
    auto skybox = mWorld->getEntity("skybox");
    ch::Skybox skyboxComp;
    mWorld->unpack(skybox, skyboxComp);
    skyboxComp().mSkyboxShader.use();
    skyboxComp().mSkyboxShader.setMat4("projection", projection);
    skyboxComp().mSkyboxShader.setMat4("view", view);
    skyboxComp().mDefaultShader.use();
}
