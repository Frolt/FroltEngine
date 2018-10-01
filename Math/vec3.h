#ifndef VEC3_H
#define VEC3_H

#include <ostream>
#include <vector>
#include <array>
#include <QDebug>

namespace am
{
    struct Vec3
    {
        // Constructor
        Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
        Vec3(const int v);
        Vec3(const double v);

        // Operators
        Vec3 operator+(const Vec3 &rhs) const;					// v + v
        Vec3 operator-(const Vec3 &rhs) const;					// v - v
        Vec3 &operator+=(const Vec3 &rhs);                      // v += v
        Vec3 &operator-=(const Vec3 &rhs);                      // v -= v
        Vec3 operator-() const;									// -v
        Vec3 operator*(float rhs) const;						// v * f
        friend Vec3 operator*(const Vec3 &lhs, const Vec3 &rhs);// v * v
        friend Vec3 operator*(float lhs, const Vec3 &rhs);      // f * v

        // Functions
        float length() const;
        void normalize();
        void print();
        float yaw();
        float pitch();
        float roll();
        std::array<float, 3> getArray() const;
        friend QDebug operator<<(QDebug out, const Vec3 &rhs);
        friend std::ostream &operator<<(std::ostream &out, const Vec3 &rhs);

        float x;
        float y;
        float z;
    };

    Vec3 cross(const Vec3 &v1, const Vec3 &v2);
    float dot(const Vec3 &v1, const Vec3 &v2);
    Vec3 normalize(const Vec3 &v);
}

#endif // VEC3_H
