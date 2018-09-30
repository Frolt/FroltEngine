#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "a_math.h"
#include "ECS/component.h"

struct TransformComponent : public Component<TransformComponent>
{
    am::Vec3 mPosition{0};
    am::Vec3 mScale{1};
    am::Vec3 mEulerAngles{0};
};

#endif // TRANSFORMCOMPONENT_H
