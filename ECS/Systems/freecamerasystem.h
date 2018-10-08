#ifndef FREECAMERASYSTEM_H
#define FREECAMERASYSTEM_H

#include "ECS/system.h"

class FreeCameraSystem : public System
{
public:
    FreeCameraSystem();
    void beginPlay() override;
    void update(float deltaTime) override;

private:
    void processKeyboard(InputComponent &input, MovementComponent &movement, FreeCameraComponent &freeCamera, float deltaTime);
    void processMouse(InputComponent &input, FreeCameraComponent &freeCamera, TransformComponent &transform);
    void processScroll();
    void updateCameraVectors(TransformComponent &transform, FreeCameraComponent &freeCamera);
    void updateUniforms(TransformComponent &transform, FreeCameraComponent &freeCamera, CameraComponent &camera);
};

#endif // FREECAMERASYSTEM_H
