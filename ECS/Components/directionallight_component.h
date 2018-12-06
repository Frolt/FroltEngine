#ifndef DIRECTIONALLIGHT_COMPONENT_H
#define DIRECTIONALLIGHT_COMPONENT_H

#include "ECS/Components/light_component.h"
#include "ECS/component.h"


struct DirectionalLightComponent : public LightComponent, public Component<DirectionalLightComponent>
{
    DirectionalLightComponent(const am::Vec3 &dir = -am::up(), const am::Vec3 &diff = {1}, const am::Vec3 &amb = {0.1});

    am::Vec3 mDir;
    am::Vec3 mAmb{0.1};
};

#endif // DIRECTIONALLIGHT_COMPONENT_H
