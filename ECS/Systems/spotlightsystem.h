#ifndef SPOTLIGHTSYSTEM_H
#define SPOTLIGHTSYSTEM_H

#include "ECS/system.h"

// Forward declarations
struct SpotlightComponent;
struct TransformComponent;

struct SpotlightSystem : public System
{
public:
    SpotlightSystem();

    void beginPlay() override;
    void update(float) override;
    void updateUniforms(const SpotlightComponent &dirLight, const TransformComponent &transform) const;

};

#endif // SPOTLIGHTSYSTEM_H
