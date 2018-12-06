#include "spotlight_component.h"


SpotlightComponent::SpotlightComponent(int lightInstance, const am::Vec3 &dir, const am::Vec3 &diff)
    : LightComponent(diff), mLightInstance{lightInstance}, mDir{dir}
{

}
