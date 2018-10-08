#ifndef DIRECTIONALLIGHTSYSTEM_H
#define DIRECTIONALLIGHTSYSTEM_H

#include "ECS/system.h"

struct DirectionalLightSystem : public System
{
public:
    DirectionalLightSystem();

    void beginPlay() override;
    void update(float) override;
    void updateUniforms(const DirectionalLightComponent &dirLight) const;
};

#endif // DIRECTIONALLIGHTSYSTEM_H
