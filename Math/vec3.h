#ifndef VEC3_H
#define VEC3_H

#include <ostream>
#include <vector>
#include <array>
#include <QDebug>

namespace am
{
    // Forward declarations
    struct Vec4;
    struct Vec3;

    // Type alias
    using Vec = Vec3;
    using Color = Vec3;
    using Rotator = Vec3;

    struct Vec3
    {
        // Constructor
        Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
        Vec3(const int v);
        Vec3(const double v);
        Vec3(const Vec4 &vec4);

        // Operators
        Vec3 operator+(const Vec3 &rhs) const;					// v + v
        Vec3 operator-(const Vec3 &rhs) const;					// v - v
        Vec3 &operator+=(const Vec3 &rhs);                      // v += v
        Vec3 &operator-=(const Vec3 &rhs);                      // v -= v
        Vec3 &operator+=(float rhs);                            // v += f
        Vec3 &operator-=(float rhs);                            // v -= f
        Vec3 operator-() const;									// -v
        Vec3 operator*(float rhs) const;						// v * f
        Vec3 operator*=(float rhs);                             // v *= f
        friend Vec3 operator*(float lhs, const Vec3 &rhs);      // f * v
        friend Vec3 operator*(const Vec3 &lhs, const Vec3 &rhs);// v * v
        friend Vec3 operator*(float lhs, const Vec3 &rhs);      // f * v

        // Functions
        float length() const;
        void normalize();
        void print();
        const float *data() const;
        friend QDebug operator<<(QDebug out, const Vec3 &rhs);
        friend std::ostream &operator<<(std::ostream &out, const Vec3 &rhs);

        union
        {
            struct
            {
                float x, y, z;
            };
            struct
            {
                float r, g, b;
            };
            struct
            {
                float pitch, yaw, roll;
            };
        };
    };

    Vec3 cross(const Vec3 &a, const Vec3 &b);
    float dot(const Vec3 &v1, const Vec3 &b);
    Vec3 normalize(const Vec3 &v);
    Vec3 projection(const Vec3 &a, const Vec3 &b);
}

#endif // VEC3_H
