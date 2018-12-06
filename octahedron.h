#ifndef OCTAHEDRON_H
#define OCTAHEDRON_H

#include "a_math.h"
#include "vertex.h"


/**
   @brief The Octahedron class is used to create spheres
 */
class Octahedron
{
public:
    Octahedron(unsigned int n = 0);

    void makeTriangle(const am::Vec3& v1, const am::Vec3& v2, const am::Vec3& v3);
    void subDivide(const am::Vec3& a, const am::Vec3& b, const am::Vec3& c, unsigned int n);
    void makeUnitOctahedron();
    const std::vector<Vertex> &getVertices();

private:
    std::vector<Vertex> mVertices;
    unsigned int mRecursions;
    unsigned int mIndex{0};
    float mRadius{1.0f};
};

#endif // OCTAHEDRON_H
