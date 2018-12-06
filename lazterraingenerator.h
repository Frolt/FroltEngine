#ifndef LAZTERRAINGENERATOR_H
#define LAZTERRAINGENERATOR_H

#include <string>
#include <vector>
#include "vertex.h"


/**
   @brief The LazTerrainGenerator class is used to build a terrain mesh from a las file (lidar point cloud data)

    It makes the mesh with indices istead of duplicate verticecs.
    It can also specify the resolution of the terrain
 */
class LazTerrainGenerator
{
public:
    LazTerrainGenerator(const std::string &path = "data.las", float res = 1.0f);

private:
    void makeIndices();
    void calcNormals();

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
