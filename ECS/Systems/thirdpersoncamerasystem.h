#ifndef THIRDPERSONCAMERASYSTEM_H
#define THIRDPERSONCAMERASYSTEM_H

#include "ECS/system.h"

class ThirdPersonCameraSystem : public System
{
public:
    ThirdPersonCameraSystem();

    void beginPlay() override;
    void update(float deltaTime) override;
    void processMouse(const InputComponent &input, TransformComponent &transform, ThirdPersonCameraComponent &camera);
    void updateViewMatrixUniform(const ThirdPersonCameraComponent &camera, const TransformComponent &transform, EntityHandle entity);
};

#endif // THIRDPERSONCAMERASYSTEM_H
