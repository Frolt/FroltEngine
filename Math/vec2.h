#ifndef VEC2_H
#define VEC2_H

#include <vector>
#include <array>
#include <QDebug>


namespace am
{
// Forward declarations
struct Vec3;
struct Vec4;
    struct Vec2
    {
        // Constructor
        Vec2(float x = 0.0f, float y = 0.0f);
        Vec2(const int v);
        Vec2(const double v);
        Vec2(const Vec3 &vec3);
        Vec2(const Vec4 &vec4);

        // Operators
        Vec2 operator+ (const Vec2 &rhs) const;                 // v + v
        Vec2 operator- (const Vec2 &rhs) const;                 // v - v
        Vec2 &operator+=(const Vec2 &rhs);                      // v += v
        Vec2 &operator-=(const Vec2 &rhs);                      // v -= v
        Vec2 operator-() const;									// -v
        Vec2 operator*(float lhs) const;						// v * f
        friend Vec2 operator*(const Vec2 &lhs, const Vec2 &rhs);// v * v
        friend Vec3 operator*(float lhs, const Vec3 &rhs);      // f * v
        friend Vec2 operator/(float lhs, const Vec2 &rhs);      // f / v
        friend Vec2 operator/(const Vec2 &lhs, float rhs);      // v / f

        // Functions
        float length() const;
        void normalize();
        Vec3 barycentricCoordinates(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3);
        void print();
        friend std::ostream &operator<<(std::ostream &out, const Vec2 &rhs);
        friend QDebug operator<<(QDebug out, const Vec2 &rhs);

        float x;
        float y;
    };

    float cross(const Vec2 &v1, const Vec2 &v2);
    float dot(const Vec2 &v1, const Vec2 &v2);
    Vec2 normalize(const Vec2 &v);
}

#endif // VEC2_H
