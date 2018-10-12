#include "physicssystem.h"
#include "engine.h"

PhysicsSystem::PhysicsSystem()
{
    mSystemMask.addComponent<CollisionComponent>();
    mSystemMask.addComponent<TransformComponent>();
}

void PhysicsSystem::beginPlay()
{

}

void PhysicsSystem::update(float)
{
    ch::Transform transform;
    ch::Collision collision;
    for (auto entity : mRegisteredEntities) {
        mWorld->unpack(entity, transform, collision);
        checkTerrainCollision(transform);
    }
}

void PhysicsSystem::checkTerrainCollision(TransformComponent &transform)
{
    ch::Terrain terrain;
    mWorld->unpack(mWorld->mEngine.mTerrain1, terrain);

    auto &indices = terrain().mIndices;
    auto &vertices = terrain().mVertices;
    auto objectPos = am::Vec2{transform.mPosition.x, transform.mPosition.z};
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
            transform.mPosition.y = res.x * u.y + res.y * v.y + res.z * w.y + 0.5f;
        }
    }
}
