#include "third_person_camera_component.h"


ThirdPersonCameraComponent::ThirdPersonCameraComponent(Shader shader, am::Vec3 cameraRelativeLocation)
    : CameraComponent(shader), mCameraRelativeLocation{cameraRelativeLocation}
{

}
