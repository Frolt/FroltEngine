#include "vec4.h"
#include <iostream>
#include "vec3.h"


namespace am
{
    Vec4::Vec4(float x, float y, float z, float w) :
        x{ x }, y{ y }, z{ z }, w{ w }
    {
    }

    Vec4::Vec4(const Vec3 &v3) :
        x{v3.x}, y{v3.y}, z{v3.z}, w{1.0f}
    {
    }

    Vec4::Vec4(const int v) :
        x{static_cast<float>(v)}, y{static_cast<float>(v)}, z{static_cast<float>(v)}, w{1.0f}
    {
    }

    Vec4::Vec4(const double v)
        : x{static_cast<float>(v)}, y{static_cast<float>(v)}, z{static_cast<float>(v)}, w{1.0f}
    {
    }

    void Vec4::print()
    {
        std::cout << "(" << x << "," << y << "," << z << "," << w << ")\n";
    }

    QDebug operator<<(QDebug out, const Vec4 &rhs)
    {
        out << "(" << rhs.x << "," << rhs.y << "," << rhs.z << "," << rhs.w << ")";
        return out;
    }

    std::ostream &operator<<(std::ostream &out, const Vec4 &rhs)
    {
        out << "(" << rhs.x << "," << rhs.y << "," << rhs.z << "," << rhs.w << ")";
        return out;
    }
}
