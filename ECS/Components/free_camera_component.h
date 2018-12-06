#ifndef FREE_CAMERA_COMPONENT_H
#define FREE_CAMERA_COMPONENT_H

#include "ECS/component.h"
#include "ECS/Components/camera_component.h"
#include "a_math.h"


struct FreeCameraComponent : public CameraComponent, public Component<FreeCameraComponent>
{
    FreeCameraComponent() = default;
    FreeCameraComponent(Shader shader);

    am::Vec mFront = am::forward();
    am::Vec mUp;
    am::Vec mRight;

    float mZoomStr{5.0f};
    float mZoom{45.0f};
    float mMoveSpeed{50.0f};
    float mMoveStr{10.0f};
    float mMouseSense{0.2f};
};

#endif // FREE_CAMERA_COMPONENT_H
