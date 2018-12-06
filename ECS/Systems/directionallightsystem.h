#ifndef DIRECTIONALLIGHTSYSTEM_H
#define DIRECTIONALLIGHTSYSTEM_H

#include "ECS/system.h"


/**
   @brief The DirectionalLightSystem class simply updates the directional light shader uniforms
 */
class DirectionalLightSystem : public System
{
public:
    DirectionalLightSystem();

    void beginPlay() override;
    void update(float) override;
    void updateUniforms(const DirectionalLightComponent &dirLight) const;
};

#endif // DIRECTIONALLIGHTSYSTEM_H
