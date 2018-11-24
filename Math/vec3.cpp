#include "vec3.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "vec4.h"

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

    Vec3::Vec3(const Vec4 &vec4)
        : x{vec4.x}, y{vec4.y}, z{vec4.z}
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

    Vec3 &Vec3::operator+=(float rhs)
    {
        x+=rhs;
        y+=rhs;
        z+=rhs;
        return *this;
    }

    Vec3 &Vec3::operator-=(float rhs)
    {
        x-=rhs;
        y-=rhs;
        z-=rhs;
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

    Vec3 Vec3::operator*=(float rhs)
    {
        return {x *= rhs, y *= rhs, z *= rhs};
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

    void Vec3::print()
    {
        std::cout << "(" << x << "," << y << "," << z << ")\n";
    }

    const float * Vec3::data() const
    {
        return &x;
    }

    QDebug operator<<(QDebug out, const Vec3 &rhs)
    {
        out << "(" << rhs.x << "," << rhs.y << "," << rhs.z << ")";
        return  out;
    }

    std::ostream &operator<<(std::ostream &out, const Vec3 &rhs)
    {
        out << "(" << rhs.x << "," << rhs.y << "," << rhs.z << ")";
        return out;
    }
}

namespace am
{
    Vec3 cross(const Vec3 &a, const Vec3 &b)
    {
        return { a.y * b.z - a.z * b.y, -(a.x * b.z - a.z * b.x), a.x * b.y - a.y * b.x };
    }

    float dot(const Vec3 &a, const Vec3 &b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    Vec3 normalize(const Vec3 &v)
    {
        auto l = sqrt(pow(v.x, 2.0f) + pow(v.y, 2.0f) + pow(v.z, 2.0f));
        return { v.x / l, v.y / l, v.z / l };
    }

    Vec3 projection(const Vec3 &a, const Vec3 &b)
    {
        auto numerator = dot(a, b);
        auto denominator = a.length();
        return (numerator / std::powf(denominator, 2.0f)) * a;
    }

    Vec3 clampLength(const Vec3 &vec, float min, float max)
    {
        auto length = vec.length();
        auto unitVector = normalize(vec);
        if (length > max) {
            return unitVector * max;
        }
        if (length < min) {
            return unitVector * min;
        }
        return unitVector;
    }
}

