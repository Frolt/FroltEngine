#include "pointlight_component.h"


PointLightComponent::PointLightComponent(const am::Vec3 &amb, const am::Vec3 &diff, const am::Vec3 &spec)
    : LightComponent(amb, diff, spec)
{

}
