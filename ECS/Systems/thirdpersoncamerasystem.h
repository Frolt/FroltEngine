#ifndef THIRDPERSONCAMERASYSTEM_H
#define THIRDPERSONCAMERASYSTEM_H

#include "ECS/system.h"


/**
   @brief The ThirdPersonCameraSystem class implements a camera that always looks at the relevant entity location (usually the player)

   The cameras rotation is controlled by the mouse movement.
   The camera considers specified eye height and distance from player.
 */
class ThirdPersonCameraSystem : public System
{
public:
    ThirdPersonCameraSystem();

    void beginPlay() override;
    void update(float deltaTime) override;
    void processMouse(const InputComponent &input, TransformComponent &transform, ThirdPersonCameraComponent &camera);
    void updateViewMatrixUniform(const ThirdPersonCameraComponent &camera, EntityHandle entity);
};

#endif // THIRDPERSONCAMERASYSTEM_H
