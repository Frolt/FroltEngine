#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "a_math.h"
#include "component.h"

class TransformComponent : public Component
{
public:
    TransformComponent();
    virtual ~TransformComponent() override;

public:
    am::Vec3 mPosition;
    am::Vec3 mScale{1};
    am::Vec3 mRotation;
};

#endif // TRANSFORMCOMPONENT_H
