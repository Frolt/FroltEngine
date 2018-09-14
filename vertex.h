#ifndef VERTEX_H
#define VERTEX_H

#include "a_math.h"

struct Vertex
{
    Vertex(am::Vec3 position = {0}, am::Vec3 normal = {0}, am::Vec2 UV = {0});

    am::Vec3 mPosition{0};
    am::Vec3 mNormal{0};
    am::Vec2 mUV{0};
};

#endif // VERTEX_H
