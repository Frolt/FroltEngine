#include "pointlight_component.h"


PointLightComponent::PointLightComponent(int lightInstance, const am::Vec3 &diff)
    : LightComponent(diff), mLightInstance{lightInstance}
{

}
