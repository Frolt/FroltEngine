#ifndef TERRAINSYSTEM_H
#define TERRAINSYSTEM_H

#include "ECS/system.h"

class TerrainSystem : public System
{
public:
    TerrainSystem();

    void beginPlay() override;
    void update(float deltaTime) override;
    void applyTransformation(TerrainComponent &terrain, const TransformComponent &transform);
};

#endif // TERRAINSYSTEM_H
