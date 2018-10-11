#ifndef TERRAIN_COMPONENT_H
#define TERRAIN_COMPONENT_H

#include <vector>
#include "vertex.h"
#include "ECS/component.h"

struct TerrainComponent : public Component<TerrainComponent>
{
    bool mStatic{true};
    std::vector<Vertex> mVertices;
    std::vector<std::array<int, 6>> mTriangles;
};

#endif // TERRAIN_COMPONENT_H
