#include "aisystem.h"
#include "engine.h"


AISystem::AISystem()
{
    mSystemMask.addComponent<BSplineComponent>();
    mSystemMask.addComponent<TransformComponent>();
    mSystemMask.addComponent<AIComponent>();
}

void AISystem::beginPlay()
{
    std::vector<EntityHandle> crystals;
    unsigned int index{0};
    bool noMoreCrystals{false};
    while (noMoreCrystals == false) {
        std::string entityName = "crystal" + std::to_string(index);
        if (mWorld->entityExist(entityName)) {
            crystals.push_back(mWorld->getEntity(entityName));
            index++;
        } else {
            noMoreCrystals = true;
        }
    }
    mNumOfCrystals = static_cast<unsigned int>(crystals.size());

    ch::Transform transform;
    ch::BSpline bSpline;
    for (auto &entity : mRegisteredEntities) {
        mWorld->unpack(entity, bSpline);
        std::vector<am::Vec3> points;
        points.reserve(5);
        mWorld->unpack(mWorld->getEntity("startPos"), transform);
        points.push_back(transform().mLocation);
        for (auto &element : crystals) {
            mWorld->unpack(element, transform);
            points.push_back(transform().mLocation);
        }
        mWorld->unpack(mWorld->getEntity("endPos"), transform);
        points.push_back(transform().mLocation);
        bSpline().mPoints = points;
        updateSplineVertices(bSpline);
        mFinished = false;
        mAtStart = true;
    }
}

void AISystem::update(float deltaTime)
{
    ch::Transform transform;
    ch::BSpline bSpline;
    for (auto &entity : mRegisteredEntities) {
        mWorld->unpack(entity, transform, bSpline);
        moveNPC(deltaTime, bSpline, transform);
        if (mFinished) {
            getNewPath(bSpline);
//            updateSplineVertices(bSpline);
            mFinished = false;
        }
//        drawSpline(bSpline);
//        addTerrainCollision(transform);
    }
}

void AISystem::moveNPC(float deltaTime, BSplineComponent &bSpline, TransformComponent &transform)
{
    std::vector<EntityHandle> crystals;
    crystals.reserve(3);
    for (unsigned int i = 0; i < mNumOfCrystals; i++) {
        std::string entityName = "crystal" + std::to_string(i);
        if (mWorld->entityExist(entityName)) {
            crystals.push_back(mWorld->getEntity(entityName));
        }
    }
    auto activeCrystals = crystals.size();

    // MAKE KNOT VECTOR
    unsigned int degree = bSpline.mDegree;
    unsigned int numOfPoints = static_cast<unsigned int>(bSpline.mPoints.size());
    unsigned int knots = degree + numOfPoints + 1;
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

    // Calculate x value
    float vel = 0.2f * deltaTime;
    static float x = 0.0f;
    x+= vel;
    if (activeCrystals == 0) {
        return; // chase player
    }
    if (x >= 1.0f) {
        x = 0.0f;
        mFinished = true;
        if (mAtStart)
            mAtStart = false;
        else
            mAtStart = true;
        return;
    }
    transform.mLocation = am::bSpline(bSpline.mPoints, t, x, degree);
}

void AISystem::getNewPath(BSplineComponent &bSpline)
{
    ch::Transform transform;
    std::vector<am::Vec3> points;
    points.reserve(5);
    // insert start point
    if (mAtStart) {
        mWorld->unpack(mWorld->getEntity("startPos"), transform);
        points.push_back(transform().mLocation);
    } else {
        mWorld->unpack(mWorld->getEntity("endPos"), transform);
        points.push_back(transform().mLocation);
    }
    // insert crystal points
    auto rand1 = (std::rand() % 3);
    auto rand2 = (std::rand() % 3);
    auto rand3 = (std::rand() % 3);
    std::string name = "crystal" + std::to_string(rand1);
    if (mWorld->entityExist(name)) {
        mWorld->unpack(mWorld->getEntity(name), transform);
        points.push_back(transform().mLocation);
    }
    while (rand2 == rand1) {
        rand2 = (std::rand() % 3);
    }
    name = "crystal" + std::to_string(rand2);
    if (mWorld->entityExist(name)) {
        mWorld->unpack(mWorld->getEntity(name), transform);
        points.push_back(transform().mLocation);
    }
    while (rand3 == rand1 || rand3 == rand2) {
        rand3 = (std::rand() % 3);
    }
    name = "crystal" + std::to_string(rand3);
    if (mWorld->entityExist(name)) {
        mWorld->unpack(mWorld->getEntity(name), transform);
        points.push_back(transform().mLocation);
    }

    // insert end point
    if (mAtStart) {
        mWorld->unpack(mWorld->getEntity("endPos"), transform);
        points.push_back(transform().mLocation);
    } else {
        mWorld->unpack(mWorld->getEntity("startPos"), transform);
        points.push_back(transform().mLocation);
    }
    bSpline.mPoints = points;
}

void AISystem::updateSplineVertices(BSplineComponent &bSpline)
{
    unsigned int res = 100.0f;
    unsigned int degree = bSpline.mDegree;

    // MAKE KNOT VECTOR
    unsigned int numOfPoints = static_cast<unsigned int>(bSpline.mPoints.size());
    unsigned int knots = degree + numOfPoints + 1;
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

    for (float x = 0.0f; x <= 1.0f; x+=delta)
        bSpline.mVertices.emplace_back(am::bSpline(bSpline.mPoints, t, x, degree));
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

void AISystem::addTerrainCollision(TransformComponent &transform)
{
    ch::Terrain terrain;
    mWorld->unpack(mWorld->getEntity("mathTerrain"), terrain);

    auto &indices = terrain().mIndices;
    auto &vertices = terrain().mVertices;
    auto objectPos = am::Vec2{transform.mLocation.x, transform.mLocation.z};
    am::Vec3 res;

    for (unsigned int i = 0; i < indices.size(); i+=3) {
        am::Vec2 a = am::Vec2(vertices[indices[i]].mPosition.x, vertices[indices[i]].mPosition.z);
        am::Vec2 b = am::Vec2(vertices[indices[i+1]].mPosition.x, vertices[indices[i+1]].mPosition.z);
        am::Vec2 c = am::Vec2(vertices[indices[i+2]].mPosition.x, vertices[indices[i+2]].mPosition.z);
        res = -objectPos.barycentricCoordinates(a,b,c);
        if (res.x >= 0 && res.y >= 0 && res.z >= 0) {
            auto u = vertices[indices[i]].mPosition;
            auto v = vertices[indices[i+1]].mPosition;
            auto w = vertices[indices[i+2]].mPosition;
            transform.mLocation.y = res.x * u.y + res.y * v.y + res.z * w.y + 0.5f;
        }
    }
}
