#ifndef TERRAIN_COMPONENT_H
#define TERRAIN_COMPONENT_H

#include <vector>
#include "vertex.h"
#include "ECS/component.h"


struct TerrainComponent : public Component<TerrainComponent>
{
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
};

#endif // TERRAIN_COMPONENT_H
