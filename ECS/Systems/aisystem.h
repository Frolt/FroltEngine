#ifndef AISYSTEM_H
#define AISYSTEM_H

#include "ECS/system.h"
#include <QOpenGLFunctions_4_1_Core>


/**
   @brief Implements AI behavior
 */
class AISystem : public System, protected QOpenGLFunctions_4_1_Core
{
public:
    AISystem();

    void beginPlay() override;
    void update(float deltaTime) override;

    void moveNPC(float deltaTime, BSplineComponent &bSpline, TransformComponent &transform);
    void getNewPath(BSplineComponent &bSpline);
    void updateSplineVertices(BSplineComponent &bSpline);
    void drawSpline(BSplineComponent &bSpline);
    void addTerrainCollision(TransformComponent &transform);

private:
    unsigned int mNumOfCrystals{0};
    bool mFinished{true};
    bool mAtStart{true};
};

#endif // AISYSTEM_H
