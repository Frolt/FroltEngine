#include "directionallight_component.h"


DirectionalLightComponent::DirectionalLightComponent(const am::Vec3 &dir, const am::Vec3 &amb,
                                                     const am::Vec3 &diff, const am::Vec3 &spec)
    : LightComponent(amb, diff, spec), mDir{dir}
{

}
