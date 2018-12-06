#ifndef LIGHT_COMPONENT_H
#define LIGHT_COMPONENT_H

#include "a_math.h"
#include "shader.h"


struct LightComponent
{
protected:
    LightComponent() = default;
    virtual ~LightComponent() = default;
    LightComponent(const am::Vec3 &diff);

public:
    Shader mShader;
    am::Vec3 mDiff{1};
};

#endif // LIGHT_COMPONENT_H
