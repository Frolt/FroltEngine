#include "bspline_component.h"

BSplineComponent::BSplineComponent()
{
    am::Vec3 A{-10.0f, 10.0f, 0.0f};
    am::Vec3 B{-5.0f, 20.0f, 0.0f};
    am::Vec3 C{5.0f, 20.0f, 0.0f};
    am::Vec3 D{10.0f, 10.0f, 0.0f};
    am::Vec3 E{20.0f, 30.0f, 0.0f};
    mPoints.push_back(A);
    mPoints.push_back(B);
    mPoints.push_back(C);
    mPoints.push_back(D);
    mPoints.push_back(E);
}
