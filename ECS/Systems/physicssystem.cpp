#include "physicssystem.h"
#include "engine.h"

PhysicsSystem::PhysicsSystem()
{
    mSystemMask.addComponent<PhysicsComponent>();
    mSystemMask.addComponent<TransformComponent>();
    mSystemMask.addComponent<MovementComponent>();
}

void PhysicsSystem::beginPlay()
{

}

void PhysicsSystem::update(float)
{
    ch::Transform transform;
    ch::Physics physics;
    ch::Movement movement;
    for (auto entity : mRegisteredEntities) {
        mWorld->unpack(entity, transform, physics, movement);
        applyGravity(transform, movement, physics);
//        checkTerrainCollision(transform);
    }
}

void PhysicsSystem::applyGravity(TransformComponent &transform, MovementComponent &movement, PhysicsComponent &physics)
{
    ch::Terrain terrain;
    mWorld->unpack(mWorld->mEngine.mTerrain1, terrain);

    auto &indices = terrain().mIndices;
    auto &vertices = terrain().mVertices;
    auto objectPos = am::Vec2{transform.mPosition.x, transform.mPosition.z};
    am::Vec3 P;
    am::Vec3 Q;
    am::Vec3 R;
    am::Vec3 normal;
    am::Vec3 G{0.0f, -am::GRAVITY, 0.0f};
    float mass = 10.5f;
    float triangleHeight{1.0f};

    am::Vec3 res;
    for (unsigned int i = 0; i < indices.size(); i+=3) {
        am::Vec2 a = am::Vec2(vertices[indices[i]].mPosition.x, vertices[indices[i]].mPosition.z);
        am::Vec2 b = am::Vec2(vertices[indices[i+1]].mPosition.x, vertices[indices[i+1]].mPosition.z);
        am::Vec2 c = am::Vec2(vertices[indices[i+2]].mPosition.x, vertices[indices[i+2]].mPosition.z);
        res = -objectPos.barycentricCoordinates(a,b,c);
        if (res.x >= 0 && res.y >= 0 && res.z >= 0) {
            P = vertices[indices[i]].mPosition;
            Q = vertices[indices[i+1]].mPosition;
            R = vertices[indices[i+2]].mPosition;
            auto u1 = Q - P;
            auto u2 = R - P;
            normal = am::normalize(am::cross(u1, u2));
            triangleHeight = res.x * P.y + res.y * Q.y + res.z * R.y;
            break;
        }
    }
    am::Vec3 N;
    if (transform.mPosition.y >= triangleHeight + 1.0f) {
        N = am::zero();
    } else {
        transform.mPosition.y = triangleHeight + 1.0f;
        N = normal * G.length() * normal.y;
    }
    movement.mVelocity += (1.0f / mass) * (N + G);
    movement.mVelocity *= 0.999f;
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
