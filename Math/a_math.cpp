#include "a_math.h"
#include <QDebug>
#include <array>
#include <QElapsedTimer>

namespace am
{
    float toDegrees(float rad)
    {
        return rad * (180.f / PI);
    }

    float toRadians(float deg)
    {
        return deg * (PI / 180.f);
    }

    float mod(float x, float y)
    {
        // same as (x % y)
        int timesY = static_cast<int>(x / y);
        return x - (timesY * y);
    }

    Vec3 bezierCurve(std::vector<Vec3> points, float t, int degree)
    {
        for (int k = 0; k < degree; ++k) {
            for (int i = 0; i < degree - k; ++i)
                points[i] = points[i] * (1.0f - t) + points[i+1] * t;
        }
        return points[0];
    }

    Vec3 bSpline(const std::vector<Vec3>& points, const std::vector<float>& t, float x, unsigned int degree)
    {
        // CALCULATE VALID KNOT INTERVAL 'MY'
        int my;
        for (my = 0; my < static_cast<int>(points.size()); my++) {
            if (x < t[my+1])
                break;
        }

        // CALCULATE BASIS FUNCTIONS
        std::vector<float> basis(t.size());
        for (unsigned int j = 0; j <= degree; j++) {
            for (int i = (my-j); i <= my; i++) {
                if (j == 0) {
                    basis[i] = 1.0f;
                } else {
                    float left, right;
                    if (basis[i] != 0.0f)
                        left = ((x - t[i]) / (t[i+j] - t[i])) * basis[i];
                    else
                        left = 0.0f;
                    if (basis[i+1] != 0.0f)
                        right = ((t[i+j+1] - x) / (t[i+j+1] - t[i+1])) * basis[i+1];
                    else
                        right = 0.0f;
                    basis[i] = left + right;
                }
            }
        }
        // MULTIPLY POINTS WITH BASIS FUNCTIONS
        Vec3 result;
        for (int i = 0; i < static_cast<int>(points.size()); i++)
            result += basis[i] * points[i];
        return result;
    }

    Vec3 up()
    {
        return Vec3(0.0f, 1.0f, 0.0f);
    }

    Vec3 right()
    {
        return Vec3(1.0f, 0.0f, 0.0f);
    }

    Vec3 forward()
    {
        return Vec3(0.0f, 0.0f, 1.0f);
    }

    Vec3 one()
    {
        return Vec3(1.0f, 1.0f, 1.0f);
    }

    Vec3 zero()
    {
        return Vec3(0.0f, 0.0f, 0.0f);
    }

    float clamp(float x, float min, float max)
    {
        if (x < min)
            x = min;
        else if (x > max)
            x = max;
        return x;
    }
}
