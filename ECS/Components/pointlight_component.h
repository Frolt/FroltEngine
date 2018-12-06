#ifndef POINTLIGHT_COMPONENT_H
#define POINTLIGHT_COMPONENT_H

#include "ECS/Components/light_component.h"
#include "ECS/component.h"


struct PointLightComponent : public LightComponent, public Component<PointLightComponent>
{
    PointLightComponent() = default;
    PointLightComponent(int lightInstance, const am::Vec3 &diff = {1});

    int mLightInstance;
    float mConstant{1.0f};
    float mLinear{0.014f};
    float mQuadratic{0.0007f};
};

#endif // POINTLIGHT_COMPONENT_H
