#ifndef SPOTLIGHT_COMPONENT_H
#define SPOTLIGHT_COMPONENT_H

#include "ECS/Components/light_component.h"
#include "ECS/component.h"
#include "a_math.h"


struct SpotlightComponent : public LightComponent, public Component<SpotlightComponent>
{
    SpotlightComponent() = default;
    SpotlightComponent(int lightInstance, const am::Vec3 &dir = -am::up(), const am::Vec3 &diff = {1});

    int mLightInstance;
    am::Vec3 mDir;
    float mInnerCone{30.0f};
    float mOuterCone{40.0f};
    float mConstant{1.0f};
    float mLinear{0.014f};
    float mQuadratic{0.0007f};
};

#endif // SPOTLIGHT_COMPONENT_H
