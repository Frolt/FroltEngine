#ifndef DIRECTIONALLIGHTSYSTEM_H
#define DIRECTIONALLIGHTSYSTEM_H

#include "ECS/system.h"

// Forward declarations
struct DirectionalLightComponent;

struct DirectionalLightSystem : public System
{
public:
    DirectionalLightSystem();

    void beginPlay() override;
    void update(float) override;
    void setUniforms(const DirectionalLightComponent &dirLight) const;
};

#endif // DIRECTIONALLIGHTSYSTEM_H
