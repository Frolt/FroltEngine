#include "aisystem.h"

AISystem::AISystem()
{
    mSystemMask.addComponent<BSplineComponent>();
    mSystemMask.addComponent<TransformComponent>();
}

void AISystem::beginPlay()
{

}

void AISystem::update(float)
{
    ch::Transform transform;
    ch::Bspline bSpline;
    for (auto entity : mRegisteredEntities) {
        mWorld->unpack(entity, transform, bSpline);
        updateSpline(bSpline);
        drawSpline(bSpline);
//        transform().mPosition.x = sin()
    }
}

void AISystem::updateSpline(BSplineComponent &bSpline)
{
    unsigned int res = 10.0f;
    unsigned int degree = 3;

    // MAKE KNOT VECTOR
    unsigned int knots = degree + static_cast<unsigned int>(bSpline.mPoints.size()) + 1;
    std::vector<float> t(knots);
    float m = knots - (degree+1) * 2.0f + 1.0f;
    float deltaKnots = 1.0f / m;
    for (unsigned int i = 0; i < knots; i++) {
        if (i <= degree)
            t[i] = 0.0f;
        else if (i >= (knots - (degree + 1)))
            t[i] = 1.0f;
        else
            t[i] = t[i-1] + deltaKnots;
    }


    // SENDS X VALUE INTO B-SPLINE FUNCTION
    float delta = 1.0f / res;
    float x = 0.0f;

    for (unsigned int i = 0; i < res+1; ++i) {
        bSpline.mVertices.push_back(Vertex{am::bSpline(bSpline.mPoints, t, x, degree)});
        x += delta;
    }
    qDebug() << bSpline.mVertices.size();
//    qDebug() << bSpline.mVertices[27].mPosition;
//    qDebug() << bSpline.mVertices[29].mPosition;
}

void AISystem::drawSpline(BSplineComponent &bSpline)
{
    initializeOpenGLFunctions();
    unsigned int VAO, VBO;
    // Activate VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // Buffer vertices
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, bSpline.mVertices.size() * sizeof(Vertex), bSpline.mVertices.data(), GL_STATIC_DRAW);
    // Vertex attribute settings
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mPosition));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mNormal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mUV));
    // Enable attributes
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glDrawArrays(GL_LINE_STRIP, 0, static_cast<int>(bSpline.mVertices.size()));
}
