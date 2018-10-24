#ifndef AISYSTEM_H
#define AISYSTEM_H

#include "ECS/system.h"
#include <QOpenGLFunctions_4_1_Core>

class AISystem : public System, protected QOpenGLFunctions_4_1_Core
{
public:
    AISystem();

    void beginPlay() override;
    void update(float deltaTime) override;
    void updateSpline(BSplineComponent &bSpline);
    void drawSpline(BSplineComponent &bSpline);
};

#endif // AISYSTEM_H
