#ifndef BSPLINE_COMPONENT_H
#define BSPLINE_COMPONENT_H

#include "ECS/component.h"
#include <vector>
#include "vertex.h"


struct BSplineComponent : public Component<BSplineComponent>
{
    BSplineComponent();
    std::vector<am::Vec3> mPoints;
    std::vector<Vertex> mVertices;
    unsigned int mDegree{2};
};

#endif // BSPLINE_COMPONENT_H
