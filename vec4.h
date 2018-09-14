#ifndef VEC4_H
#define VEC4_H


#include "vec3.h"
#include <QDebug>

namespace am
{
    struct Vec4
    {
        Vec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
        Vec4(const Vec3 &v3);
        Vec4(const int v);
        Vec4(const double v);

        void print();
        friend std::ostream &operator<<(std::ostream &out, const Vec4 &rhs);
        friend QDebug operator<<(QDebug out, const Vec4 &rhs);

        float x;
        float y;
        float z;
        float w;
    };
}
#endif // VEC4_H
