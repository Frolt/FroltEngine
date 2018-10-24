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
};

#endif // BSPLINE_COMPONENT_H
