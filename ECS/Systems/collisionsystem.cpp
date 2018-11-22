#include "collisionsystem.h"
#include "engine.h"

CollisionSystem::CollisionSystem()
{
    mSystemMask.addComponent<CollisionComponent>();
}

void CollisionSystem::beginPlay()
{

}

void CollisionSystem::update(float)
{
    EntityHandle player = mWorld->getEntity("player");
    for (auto &entity : mRegisteredEntities) {
        // Check for terrain collision
        checkTerrainCollision(entity);
        // Check if player hit something
        if (entity != player) {
            if (checkCollision(player, entity)) {
                mEventHandler->publish(std::make_unique<CollisionEvent>(player, entity));
            }
        }
    }
}

bool CollisionSystem::checkCollision(EntityID entity1, EntityID entity2)
{
    ch::Transform transform;
    ch::Collision collision;

    mWorld->unpack(entity1, transform, collision);
    auto aPos = transform().mLocation;
    auto aSize = collision().mSize;
    aPos.x -= aSize.x;
    aPos.y += aSize.y;
    aPos.z -= aSize.z;

    mWorld->unpack(entity2, transform, collision);
    auto bPos = transform().mLocation;
    auto bSize = collision().mSize;
    bPos.x -= bSize.x;
    bPos.y += bSize.y;
    bPos.z -= bSize.z;

    aSize *= 2.0f;
    bSize *= 2.0f;

    bool collisionX = (aPos.x + aSize.x >= bPos.x) && (bPos.x + bSize.x >= aPos.x);
    bool collisionY = (aPos.y >= bPos.y - bSize.y) && (bPos.y >= aPos.y - aSize.y);
    bool collisionZ = (aPos.z + aSize.z >= bPos.z) && (bPos.z + bSize.z >= aPos.z);

    return collisionX && collisionY && collisionZ;
}

void CollisionSystem::checkTerrainCollision(EntityID entity)
{
    ch::Transform transform;
    mWorld->unpack(entity, transform);
    ch::Terrain terrain;
    mWorld->unpack(mWorld->mEngine.mTerrain1().mID, terrain);

    auto &indices = terrain().mIndices;
    auto &vertices = terrain().mVertices;
    auto objectPos = am::Vec2{transform().mLocation.x, transform().mLocation.z};
    am::Vec3 result;

    for (unsigned int i = 0; i < indices.size(); i+=3) {
        am::Vec2 a = am::Vec2(vertices[indices[i]].mPosition.x, vertices[indices[i]].mPosition.z);
        am::Vec2 b = am::Vec2(vertices[indices[i+1]].mPosition.x, vertices[indices[i+1]].mPosition.z);
        am::Vec2 c = am::Vec2(vertices[indices[i+2]].mPosition.x, vertices[indices[i+2]].mPosition.z);
        result = -objectPos.barycentricCoordinates(a,b,c);
        if (result.x >= 0 && result.y >= 0 && result.z >= 0) {
            auto u = vertices[indices[i]].mPosition;
            auto v = vertices[indices[i+1]].mPosition;
            auto w = vertices[indices[i+2]].mPosition;
            float yValue = result.x * u.y + result.y * v.y + result.z * w.y + 0.5f;
            if (transform().mLocation.y < yValue)
                transform().mLocation.y = yValue;
        }
    }
}
