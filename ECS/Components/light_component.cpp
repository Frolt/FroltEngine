#include "light_component.h"


LightComponent::LightComponent(const am::Vec3 &amb, const am::Vec3 &diff, const am::Vec3 &spec)
    :mAmb{amb}, mDiff{diff}, mSpec{spec}
{

}
