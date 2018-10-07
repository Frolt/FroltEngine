#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "a_math.h"
#include "ECS/component.h"

struct TransformComponent : public Component<TransformComponent>
{
    TransformComponent(const am::Vec3 &pos = {0}, const am::Vec3 &scale = {1}, const am::Vec3 &eulerAngles = {0});

    am::Vec3 mPosition;
    am::Vec3 mScale;
    am::Vec3 mEulerAngles;
};

#endif // TRANSFORM_COMPONENT_H
