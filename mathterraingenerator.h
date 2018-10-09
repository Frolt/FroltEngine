#ifndef MATHTERRAINGENERATOR_H
#define MATHTERRAINGENERATOR_H

#include <vector>
#include <array>
#include "vertex.h"

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
    unsigned int mVAO{0};
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
    std::vector<std::array<int, 6>> mTriangles;
};

#endif // MATHTERRAINGENERATOR_H
