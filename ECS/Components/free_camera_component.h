#ifndef FREE_CAMERA_COMPONENT_H
#define FREE_CAMERA_COMPONENT_H

#include "ECS/component.h"
#include "a_math.h"

struct FreeCameraComponent : public Component<FreeCameraComponent>
{
    FreeCameraComponent() = default;

    // TODO use velocity in movementComponent?
    am::Vec mFront = -am::forward();
    am::Vec mUp;
    am::Vec mRight;
    am::Vec mWorldUp = am::up();

    float mAspect{0.0f};
    float mMoveSpeed{50.0f};
    float mMoveStr{10.0f};
    float mMouseSense{0.3f};
};

#endif // FREE_CAMERA_COMPONENT_H
