#ifndef MATH_TERRAIN_COMPONENT_H
#define MATH_TERRAIN_COMPONENT_H

#include <vector>
#include "vertex.h"
#include "ECS/component.h"

struct MathTerrainComponent : public Component<MathTerrainComponent>
{
    MathTerrainComponent() = default;

    std::vector<Vertex> mVertices;
    std::vector<std::array<int, 6>> mTriangles;
};

#endif // MATH_TERRAIN_COMPONENT_H
