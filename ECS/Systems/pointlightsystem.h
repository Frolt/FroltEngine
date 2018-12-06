#ifndef POINTLIGHTSYSTEM_H
#define POINTLIGHTSYSTEM_H

#include "ECS/system.h"


/**
   @brief The PointLightSystem class simply updates the shader uniforms for all point lights
 */
class PointLightSystem : public System
{
public:
    PointLightSystem();

    void beginPlay() override;
    void update(float) override;
    void updateUniforms(const PointLightComponent &dirLight, const TransformComponent &transform) const;


};

#endif // POINTLIGHTSYSTEM_H
