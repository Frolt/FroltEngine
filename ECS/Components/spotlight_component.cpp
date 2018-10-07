#include "spotlight_component.h"


SpotlightComponent::SpotlightComponent(const am::Vec3 &dir, const am::Vec3 &amb,
                                       const am::Vec3 &diff, const am::Vec3 &spec)
    : LightComponent(amb, diff, spec), mDir{dir}
{

}
