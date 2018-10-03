#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "a_math.h"
#include "ECS/component.h"

struct TransformComponent : public Component<TransformComponent>
{
    TransformComponent() {}
    TransformComponent(am::Vec3 pos, am::Vec3 scale = {1}, am::Vec3 eulerAngles = {0})
        : mPosition{pos}, mScale{scale}, mEulerAngles{eulerAngles} {}

    am::Vec3 mPosition{0};
    am::Vec3 mScale{1};
    am::Vec3 mEulerAngles{0};
};

#endif // TRANSFORM_COMPONENT_H
