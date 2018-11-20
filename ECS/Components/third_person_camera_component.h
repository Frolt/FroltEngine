#ifndef THIRD_PERSON_CAMERA_COMPONENT_H
#define THIRD_PERSON_CAMERA_COMPONENT_H

#include "ECS/component.h"
#include "ECS/Components/camera_component.h"
#include "a_math.h"

struct ThirdPersonCameraComponent : public Component<ThirdPersonCameraComponent>, public CameraComponent
{
    ThirdPersonCameraComponent() = default;
    ThirdPersonCameraComponent(Shader shader, am::Vec3 cameraRelativeLocation = {-15.0f, 10.0f, 0.0f});

    am::Vec3 mCameraRelativeLocation{-5.0f, 5.0f, 0.0f};
    float mEyeHeight{5.0f};
};

#endif // THIRD_PERSON_CAMERA_COMPONENT_H
