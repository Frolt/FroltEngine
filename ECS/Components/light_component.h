#ifndef LIGHT_COMPONENT_H
#define LIGHT_COMPONENT_H

#include "a_math.h"
#include "shader.h"

struct LightComponent
{
protected:
    LightComponent() = default;
    LightComponent(const am::Vec3 &amb, const am::Vec3 &diff, const am::Vec3 &spec);
public:
    Shader mShader;
    am::Vec3 mAmb{0.1};
    am::Vec3 mDiff{1};
    am::Vec3 mSpec{0.5};
};

#endif // LIGHT_COMPONENT_H
