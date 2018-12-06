#ifndef MATHTERRAINGENERATOR_H
#define MATHTERRAINGENERATOR_H

#include <vector>
#include <array>
#include "vertex.h"


/**
   @brief The MathTerrainGenerator class is used to build a terrain mesh derived from a mathematical multivariable function

    It makes the mesh with indices istead of duplicate verticecs.
    It also has a topological search algorithm to optimize barycentric coordinate searching,
    and calculate it's normals from the multivariable function
 */
class MathTerrainGenerator
{
public:
    MathTerrainGenerator(int domainMin = -100, int domainMax = 100, float resolution = 1.0f);

private:
    static float calculateY(const float x, const float z);
    am::Vec3 calculateNormal(const float x, const float z);
    void FindNeighborTriangles();
    bool topologicalSearch(int startTriangle, am::Vec2 endPos);
    void makeIndices();

public:
    int mRange{0};
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
    std::vector<std::array<int, 6>> mTriangles;
};

#endif // MATHTERRAINGENERATOR_H
