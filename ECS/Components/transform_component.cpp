#include "transform_component.h"


TransformComponent::TransformComponent(const am::Vec3 &pos, const am::Vec3 &scale, const am::Vec3 &eulerAngles)
    : mPosition{pos}, mScale{scale}, mEulerAngles{eulerAngles}
{

}

