#ifndef PLAYERSYSTEM_H
#define PLAYERSYSTEM_H

#include "ECS/system.h"

class playerSystem : public System
{
public:
    playerSystem();

    void beginPlay() override;
    void update(float deltaTime) override;
    void movePlayer(const InputComponent &input, MovementComponent &movement, float deltaTime) const;
    void moveCamera(const InputComponent &input, TransformComponent &transform, float deltaTime);
    void makeViewMatrix(CameraComponent &camera, const am::Vec &location, const am::Vec &target);
};

#endif // PLAYERSYSTEM_H
