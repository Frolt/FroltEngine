#include "lazterraingenerator.h"
#include "LAS/lasreader.h"

LazTerrainGenerator::LazTerrainGenerator(const std::string &path, float res)
    : mPath{path}
{
    LASReader lasReader(mPath);
    auto &pointData = lasReader.getPointData();
    auto &headerStock = lasReader.getHeaderStock();
    mXOffset = static_cast<unsigned int>(headerStock.Max_X - headerStock.Min_X) + 1;
    mZOffset = static_cast<unsigned int>(headerStock.Max_Y - headerStock.Min_Y) + 1;
    float aspect = static_cast<float>(mZOffset) / static_cast<float>(mXOffset);
    mXRange = mXOffset / res;
    mZRange = mXRange * aspect;

    std::vector<Vertex> grid(mXRange * mZRange);
    unsigned int index = 0;
    for (float z = 0.0f; z < mZOffset; z += res)
        for (float x = 0.0f; x < mXOffset; x += res)
            grid[index++].mPosition = am::Vec{x, 0.0f, z};

    for (auto &element : pointData) {
        auto x = static_cast<unsigned int>(element.mPosition.x / res);
        auto z = static_cast<unsigned int>(element.mPosition.z / res);
        if (x < mXRange && z < mZRange) {
            grid[x + mXRange * z].mPosition.y = element.mPosition.y;
        }
    }

    mVertices = grid;

    makeIndices();
    calcNormals();
}

void LazTerrainGenerator::makeIndices()
{
    std::vector<unsigned int> indices;
    indices.reserve((mZRange-1)*(mXRange-1));

    for (unsigned int z = 0; z < (mZRange - 1); z++) {
        for (unsigned int x = 0; x < (mXRange - 1); x++) {
            indices.push_back(x + mXRange * z);
            indices.push_back(x + mXRange * (z+1));
            indices.push_back((x+1) + mXRange * z);
            indices.push_back((x+1) + mXRange * z);
            indices.push_back(x + mXRange * (z+1));
            indices.push_back((x+1) + mXRange * (z+1));
        }
    }
    mIndices = indices;
}

void LazTerrainGenerator::calcNormals()
{
    for (unsigned int i = 0; i < mIndices.size(); i += 3) {
        auto ab =  mVertices[mIndices[i+1]].mPosition - mVertices[mIndices[i]].mPosition;
        auto ac =  mVertices[mIndices[i+2]].mPosition - mVertices[mIndices[i]].mPosition;
        auto normal = am::cross(ab, ac);
        mVertices[mIndices[i]].mNormal = normal;
        mVertices[mIndices[i+1]].mNormal = normal;
        mVertices[mIndices[i+2]].mNormal = normal;
    }
}

// TODO not belonging to generator
float LazTerrainGenerator::collision(am::Vec2 playerPos)
{
    am::Vec3 res;
    for (unsigned int i = 0; i < mIndices.size(); i+=3) {
        am::Vec2 a = am::Vec2(mVertices[mIndices[i]].mPosition.x, mVertices[mIndices[i]].mPosition.z);
        am::Vec2 b = am::Vec2(mVertices[mIndices[i+1]].mPosition.x, mVertices[mIndices[i+1]].mPosition.z);
        am::Vec2 c = am::Vec2(mVertices[mIndices[i+2]].mPosition.x, mVertices[mIndices[i+2]].mPosition.z);
        res = -playerPos.barycentricCoordinates(a,b,c);
        if (res.x >= 0 && res.y >= 0 && res.z >= 0) {
            auto aa = mVertices[mIndices[i]].mPosition;
            auto bb = mVertices[mIndices[i+1]].mPosition;
            auto cc = mVertices[mIndices[i+2]].mPosition;
            return res.x * aa.y + res.y * bb.y + res.z * cc.y;
        }
    }
    return 0.0f;
}
