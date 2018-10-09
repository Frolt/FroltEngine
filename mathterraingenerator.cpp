#include "mathterraingenerator.h"

MathTerrainGenerator::MathTerrainGenerator(int domainMin, int domainMax, float resolution)
{
    float delta = 1.0f / resolution;
    qDebug() << "domain min: " << domainMin << "domain max: " << domainMax;
    mRange = ((-domainMin + domainMax) / delta) + 1.0f;
    mVertices.resize(mRange * mRange);
    mIndices.resize(((mRange - 1) * (mRange - 1)) * 2 * 3);

    int i = 0;
    for (float z = domainMin; z <= domainMax; z += delta) {
        for (float x = domainMin; x <= domainMax; x += delta) {
            auto y = calculateY(x, z);
            auto normal = calculateNormal(x, z);
            mVertices[i++] = Vertex{ { x, y, z }, normal };
        }
    }
    makeIndices();
//    FindNeighborTriangles();
}

float MathTerrainGenerator::calculateY(const float x, const float z)
{
    float amplitude = 1.0f;
    float scaling = 0.05f;
    return amplitude * (sin(scaling * x) * (cos(scaling * z) / scaling));
}

am::Vec3 MathTerrainGenerator::calculateNormal(const float x, const float z)
{
    float dx = cos(0.05f * x) * cos(0.05f * z);
    float dz = -sin(0.05f * x) * sin(0.05f * z);

    am::Vec3 u{ 1.0f, dx, 0.0f };
    am::Vec3 v{ 0.0f, dz, 1.0f };

    return am::normalize(am::cross(v, u));
}

// TODO not part of generator
void MathTerrainGenerator::FindNeighborTriangles()
{
    // TODO cleanup
    // Create triangle array

    for (unsigned int i = 0; i < mIndices.size(); i += 3) {
        mTriangles.push_back({{static_cast<int>(mIndices[i]),
                               static_cast<int>(mIndices[i+1]),
                               static_cast<int>(mIndices[i+2]), 0, 0, 0 }});
    }

    int index1 = 0;
    for (int i = 0; i < mRange - 1; ++i) {
        for (int j = 0; j < mRange - 1; ++j) {
            // FIRST HALF OF TRIANGLES
            mTriangles[index1][3] = index1 - ((mRange - 1) * 2) + 1;
            mTriangles[index1][4] = index1 - 1;
            mTriangles[index1][5] = index1 + 1;
            // Set -1 for missing neighbor
            if (i == 0)
                mTriangles[index1][3] = -1;
            if (j == 0)
                mTriangles[index1][4] = -1;
            // SECOND HALF OF TRIANGLES
            auto index2 = index1 + 1;
            mTriangles[index2][3] = index2 + 1;
            mTriangles[index2][4] = index2 - 1;
            mTriangles[index2][5] = index2 + ((mRange - 1) * 2) - 1;
            // Set -1 for missing neighbor
            if (i == mRange - 2)
                mTriangles[index2][5] = -1;
            if (j == mRange - 2)
                mTriangles[index2][3] = -1;
            index1 += 2;
        }
    }
}

// TODO not part of generator
bool MathTerrainGenerator::topologicalSearch(int startTriangle, am::Vec2 endPos)
{
    bool found = false;
    bool done = false;
    do {
        auto result = -endPos.barycentricCoordinates(
            am::Vec2{ mVertices[mTriangles[startTriangle][0]].mPosition.x, mVertices[mTriangles[startTriangle][0]].mPosition.z },
            am::Vec2{ mVertices[mTriangles[startTriangle][1]].mPosition.x, mVertices[mTriangles[startTriangle][1]].mPosition.z },
            am::Vec2{ mVertices[mTriangles[startTriangle][2]].mPosition.x, mVertices[mTriangles[startTriangle][2]].mPosition.z }
        );
        if (result.x >= 0 && result.y >= 0 && result.z >= 0) {
            done = true;
            found = true;
        }
        else if (result.x <= result.y && result.x <= result.z)
            startTriangle = mTriangles[startTriangle][3];
        else if (result.y <= result.x && result.y <= result.z)
            startTriangle = mTriangles[startTriangle][4];
        else if (result.z <= result.x && result.z <= result.y)
            startTriangle = mTriangles[startTriangle][5];
        if (startTriangle == -1) {
            done = true;
            found = false;
        }
    } while (!done);
    return found;
}

void MathTerrainGenerator::makeIndices()
{
    int index = 0;
    for (int i = 0; i < (mRange * (mRange - 1)) - 1; ++i) {
        if ((i + 1) % mRange == 0)
            i++;
        mIndices.push_back(i + mRange);
        mIndices.push_back(i + 1);
        mIndices.push_back(i);

        mIndices.push_back(i + mRange);
        mIndices.push_back(i + mRange + 1);
        mIndices.push_back(i + 1);
        index += 6;
    }

    //TODO use this instead?
//    for (unsigned int z = 0; z < (mZRange - 1); z++) {
//        for (unsigned int x = 0; x < (mXRange - 1); x++) {
//            index.push_back(x + mXRange * z);
//            index.push_back(x + mXRange * (z+1));
//            index.push_back((x+1) + mXRange * z);
//            index.push_back((x+1) + mXRange * z);
//            index.push_back(x + mXRange * (z+1));
//            index.push_back((x+1) + mXRange * (z+1));
//        }
//    }
}
