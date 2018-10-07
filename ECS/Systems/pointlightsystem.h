#ifndef POINTLIGHTSYSTEM_H
#define POINTLIGHTSYSTEM_H

#include "ECS/system.h"

// Forward declarations
struct PointLightComponent;
struct TransformComponent;

struct PointLightSystem : public System
{
public:
    PointLightSystem();

    void beginPlay() override;
    void update(float) override;
    void setUniforms(const PointLightComponent &dirLight, const TransformComponent &transform) const;


};

#endif // POINTLIGHTSYSTEM_H
