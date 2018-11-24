#ifndef A_MATH_H
#define A_MATH_H


#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "matrix.h"
#include "math_constants.h"
#include "color.h"

/// Namespace for all math related classes and functions
namespace am
{
    // Functions
    /// from radians to degrees
    float toDegrees(float rad);
    /// from degrees to radians
    float toRadians(float deg);
    /// same as (x % y)
    float mod(float x, float y);
    /// x can't supersede the min or max value
    float clampLength(float x, float min, float max);

    // Curves
    /**
       @brief bezierCurve Creates a bezier curve point
       @param points    The curves control points
       @param t         Range must be between 0-1
       @param degree    3 degree requires 4 control points
       @return          the point on the curve that corresponds to the t value
     */
    Vec3 bezierCurve(std::vector<Vec3> points, float t, int degree = 3);
    /**
       @brief Creates a basis spline curve point
       @param points    The curves control points
       @param t         The knot vector
       @param x         Range must be between 0-1
       @param degree
       @return          the point on the curve that corresponds to the x value
     */
    Vec3 bSpline(const std::vector<Vec3>& points, const std::vector<float>& t, float x, unsigned int degree = 3);

    // Basic vector directions
    Vec3 up();
    Vec3 right();
    Vec3 forward();
    Vec3 one();
    Vec3 zero();
}

#endif // A_MATH_H
