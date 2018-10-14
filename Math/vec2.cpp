#include "vec2.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "vec3.h"
#include "vec4.h"

namespace am
{
    Vec2::Vec2(float x, float y) :
        x{ x }, y{ y }
    {
    }

    Vec2::Vec2(const int v):
        x{ static_cast<float>(v) }, y{ static_cast<float>(v) }
    {
    }

    Vec2::Vec2(const double v) :
        x{ static_cast<float>(v) }, y{ static_cast<float>(v) }
    {
    }

    Vec2::Vec2(const Vec3 &vec3)
        : x{vec3.x}, y{vec3.y}
    {
    }

    Vec2::Vec2(const Vec4 &vec4)
        : x{vec4.x}, y{vec4.y}
    {
    }

    Vec2 Vec2::operator+(const Vec2 &rhs) const
    {
        return { x + rhs.x, y + rhs.y };
    }

    Vec2 Vec2::operator-(const Vec2 &rhs) const
    {
        return { x - rhs.x, y - rhs.y };
    }

    Vec2 &Vec2::operator+=(const Vec2 &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vec2 &Vec2::operator-=(const Vec2 &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vec2 Vec2::operator-() const
    {
        return { -x, -y };
    }

    Vec2 Vec2::operator*(float lhs) const
    {
        return { x * lhs, y * lhs };
    }

    Vec2 operator/(float lhs, const Vec2 &rhs)
    {
        return {rhs.x / lhs, rhs.y / lhs};
    }

    Vec2 operator/(const Vec2 &lhs, float rhs)
    {
        return {lhs.x / rhs, lhs.y / rhs};
    }

    Vec2 operator*(const Vec2 &lhs, const Vec2 &rhs)
    {
        return { lhs.x * rhs.x, lhs.y * rhs.y };
    }

    Vec2 operator*(float lhs, const Vec2  &rhs)
    {
        return { rhs.x * lhs, rhs.y * lhs };
    }

    float Vec2::length() const
    {
        return sqrt(pow(x, 2.0f) + pow(y, 2.0f));
    }

    void Vec2::normalize()
    {
        auto l = length();
        x = x / l;
        y = y / l;
    }

    void Vec2::print()
    {
        std::cout << "(" << x << "," << y << ")\n";
    }

    Vec3 Vec2::barycentricCoordinates(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3)
    {
        Vec2 p12 = p2 - p1;
        Vec2 p13 = p3 - p1;
        Vec3 n = cross(Vec3{ p12.x, p12.y, 0.0f }, Vec3{ p13.x, p13.y, 0.0f });
        float doubleArea = cross(p12, p13);

        Vec3 result;
        // u
        Vec2 p = p2 - *this;
        Vec2 q = p3 - *this;
        n = cross(Vec3{ p.x, p.y, 0.0f }, Vec3{ q.x, q.y, 0.0f });
        result.x = n.z / doubleArea;
        // v
        p = p3 - *this;
        q = p1 - *this;
        n = cross(Vec3{ p.x, p.y, 0.0f }, Vec3{ q.x, q.y, 0.0f });
        result.y = n.z / doubleArea;
        // w
        p = p1 - *this;
        q = p2 - *this;
        n = cross(Vec3{ p.x, p.y, 0.0f }, Vec3{ q.x, q.y, 0.0f });
        result.z = n.z / doubleArea;
        return result;
    }

    QDebug operator<<(QDebug out, const Vec2 &rhs)
    {
        out << "(" << rhs.x << "," << rhs.y << ")";
        return  out;
    }

    std::ostream &operator<<(std::ostream &out, const Vec2 &rhs)
    {
        out << "(" << rhs.x << "," << rhs.y << ")";
        return out;
    }
}

namespace am
{
    float cross(const Vec2 &v1, const Vec2 &v2)
    {
        return abs((v1.x * v2.y) - (v1.y * v2.x));
    }

    float dot(const Vec2  &v1, const Vec2  &v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    Vec2 normalize(const Vec2 &v)
    {
        auto l = sqrt(pow(v.x, 2.0f) + pow(v.y, 2.0f));
        return { v.x / l, v.y / l };
    }
}
