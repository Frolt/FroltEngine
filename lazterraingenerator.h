#ifndef LAZTERRAINGENERATOR_H
#define LAZTERRAINGENERATOR_H

#include <string>
#include <vector>
#include "vertex.h"

class LazTerrainGenerator
{
public:
    LazTerrainGenerator(const std::string &path = "data.las", float res = 1.0f);

private:
    void makeIndices();
    void calcNormals();
    float collision(am::Vec2 playerPos);

public:
    std::string mPath;
    double mResolution;
    unsigned int mXOffset;
    unsigned int mZOffset;
    unsigned int mXRange;
    unsigned int mZRange;
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
};

#endif // LAZTERRAINGENERATOR_H
