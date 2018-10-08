#ifndef FREECAMERACOMPONENT_H
#define FREECAMERACOMPONENT_H

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

    float mMoveSpeed{20.0f};
    float mMouseSense{0.3f};
    float mZoom{45.0f};
    float mZoomStr{3.0f};
};

#endif // FREECAMERACOMPONENT_H
