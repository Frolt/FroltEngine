#ifndef A_MATH_H
#define A_MATH_H


#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "matrix.h"
#include "math_constants.h"
#include "color.h"

namespace am
{
    // Functions
    float toDegrees(float rad);
    float toRadians(float deg);
    float mod(float x, float y);
    float clamp(float x, float min, float max);

    // Interpolation

    // Curves
    Vec3 bezierCurve(std::vector<Vec3> points, float t, int degree = 3);
    Vec3 bSpline(const std::vector<Vec3>& points, const std::vector<float>& t, float x, unsigned int degree = 3);

    // Basic vector directions
    Vec3 up();
    Vec3 right();
    Vec3 forward();
    Vec3 one();
    Vec3 zero();
}

#endif // A_MATH_H
