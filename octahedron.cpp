#include "octahedron.h"

Octahedron::Octahedron(unsigned int n)
    : mRecursions{n}
{
    unsigned int size = 3 * 8 * static_cast<int>(pow(4, mRecursions));
    mVertices.resize(size);
    makeUnitOctahedron();
}

void Octahedron::makeTriangle(const am::Vec3 &v1, const am::Vec3 &v2, const am::Vec3 &v3)
{
    mVertices[mIndex].mPosition = v1;
    mVertices[mIndex].mNormal = v1;
    mVertices[mIndex].mUV = am::Vec2(0.0f, 0.0f);
    ++mIndex;
    mVertices[mIndex].mPosition = v2;
    mVertices[mIndex].mNormal = v2;
    mVertices[mIndex].mUV = am::Vec2(1.0f, 0.0f);
    ++mIndex;
    mVertices[mIndex].mPosition = v3;
    mVertices[mIndex].mNormal = v3;
    mVertices[mIndex].mUV = am::Vec2(0.5f, 1.0f);
    ++mIndex;
}

void Octahedron::subDivide(const am::Vec3 &a, const am::Vec3 &b, const am::Vec3 &c, int n)
{
    if (n>0) {
        am::Vec3 v1 = a + b; v1.normalize();
        am::Vec3 v2 = a + c; v2.normalize();
        am::Vec3 v3 = c + b; v3.normalize();
        subDivide(a, v1, v2, n - 1);
        subDivide(c, v2, v3, n - 1);
        subDivide(b, v3, v1, n - 1);
        subDivide(v3, v2, v1, n - 1);
    }
    else {
        makeTriangle(a, b, c);
    }
}

void Octahedron::makeUnitOctahedron()
{
    am::Vec3 v0(0, 0, 1);
    am::Vec3 v1(1, 0, 0);
    am::Vec3 v2(0, 1, 0);
    am::Vec3 v3(-1, 0, 0);
    am::Vec3 v4(0, -1, 0);
    am::Vec3 v5(0, 0, -1);

    subDivide(v0, v1, v2, mRecursions);
    subDivide(v0, v2, v3, mRecursions);
    subDivide(v0, v3, v4, mRecursions);
    subDivide(v0, v4, v1, mRecursions);
    subDivide(v5, v2, v1, mRecursions);
    subDivide(v5, v3, v2, mRecursions);
    subDivide(v5, v4, v3, mRecursions);
    subDivide(v5, v1, v4, mRecursions);
}

const std::vector<Vertex> &Octahedron::getVertices()
{
    return mVertices;
}
