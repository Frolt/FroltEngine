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
    void processKeyboard(const InputComponent &input, MovementComponent &movement, FreeCameraComponent &freeCamera) const;
    void processMouse(const InputComponent &input, const FreeCameraComponent &freeCamera, TransformComponent &transform) const;
    void processScroll(FreeCameraComponent &freeCamera, const InputComponent &input) const;
    void updateCameraVectors(const TransformComponent &transform, FreeCameraComponent &freeCamera) const;
    void updateUniforms(const TransformComponent &transform, const FreeCameraComponent &camera, EntityHandle entity) const;
};

#endif // FREECAMERASYSTEM_H
