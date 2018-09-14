#include "vec3.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>

namespace am
{
    Vec3::Vec3(float x, float y, float z) :
        x{ x }, y{ y }, z{ z }
    {
    }

    Vec3::Vec3(const int v) :
        x{static_cast<float>(v)}, y{static_cast<float>(v)}, z{static_cast<float>(v)}
    {
    }

    Vec3::Vec3(const double v) :
        x{static_cast<float>(v)}, y{static_cast<float>(v)}, z{static_cast<float>(v)}
    {
    }

    Vec3 Vec3::operator+(const Vec3 &rhs) const
    {
        return { x + rhs.x, y + rhs.y, z + rhs.z };
    }

    Vec3 &Vec3::operator+=(const Vec3 &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    Vec3 &Vec3::operator-=(const Vec3 &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    Vec3 Vec3::operator-(const Vec3 &rhs) const
    {
        return { x - rhs.x, y - rhs.y, z - rhs.z };
    }

    Vec3 Vec3::operator-() const
    {
        return { -x, -y, -z };
    }

    Vec3 operator*(const Vec3 &lhs, const Vec3 &rhs)
    {
        return { lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z };
    }

    Vec3 operator*(float lhs, const Vec3 &rhs)
    {
        return { rhs.x * lhs, rhs.y * lhs, rhs.z * lhs };
    }

    Vec3 Vec3::operator*(float rhs) const
    {
        return { x * rhs, y * rhs, z * rhs };
    }

    float Vec3::length() const
    {
        return sqrt(pow(x, 2.0f) + pow(y, 2.0f) + pow(z, 2.0f));
    }

    void Vec3::normalize()
    {
        auto l = length();
        x = x / l;
        y = y / l;
        z = z / l;
    }

    std::array<float, 3> Vec3::getArray() const
    {
        return {{ x, y, z }};
    }

    QDebug operator<<(QDebug out, const Vec3 &rhs)
    {
        out << "(" << rhs.x << "," << rhs.y << "," << rhs.z << ")";
        return  out;
    }

    void Vec3::print()
    {
        std::cout << "(" << x << "," << y << "," << z << ")\n";
    }

    std::ostream &operator<<(std::ostream &out, const Vec3 &rhs)
    {
        out << "(" << rhs.x << "," << rhs.y << "," << rhs.z << ")";
        return out;
    }
}

namespace am
{
    Vec3 cross(const Vec3 &v1, const Vec3 &v2)
    {
        return { v1.y * v2.z - v1.z * v2.y, -(v1.x * v2.z - v1.z * v2.x), v1.x * v2.y - v1.y * v2.x };
    }

    float dot(const Vec3 &v1, const Vec3 &v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    Vec3 normalize(const Vec3 &v)
    {
        auto l = sqrt(pow(v.x, 2.0f) + pow(v.y, 2.0f) + pow(v.z, 2.0f));
        return { v.x / l, v.y / l, v.z / l };
    }
}

