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
    EntityHandle player;
    EntityHandle shark;

    if (mWorld->entityExist("player"))
        player = mWorld->getEntity("player");
    if (mWorld->entityExist("shark0"))
        shark = mWorld->getEntity("shark0");

    ch::Collision collision;
    for (auto &entity : mRegisteredEntities) {
        // Check for terrain collision
        checkTerrainCollision(entity);
        // Check if player hit other box collision entities
        if (entity != player) {
            mWorld->unpack(entity, collision);
            if (collision().isBox) {
                if (checkBoxCollision(player, entity)) {
                    mEventHandler->publish(std::make_unique<CollisionEvent>(player, entity));
                }
            }
        }
        // Check if shark hit anything
        if (entity != shark) {
            mWorld->unpack(entity, collision);
            if (collision().isBox) {
                if (checkBoxCollision(shark, entity)) {
                    mEventHandler->publish(std::make_unique<CollisionEvent>(shark, entity));
                }
            }
        }
//        // Check if sphere hit something
//        mWorld->unpack(entity, collision);
//        if (collision().isBox == false) {
//            for (auto &other : mRegisteredEntities) {
//                if (entity != other) {
//                    mWorld->unpack(other, collision);
//                    if (collision().isBox == false) {
//                        if (checkSphereCollision(entity, other)) {
//                            mEventHandler->publish(std::make_unique<SphereCollisionEvent>(entity, other));
//                        }
//                    }
//                }
//            }
//        }
    }
}

bool CollisionSystem::checkBoxCollision(EntityID entity1, EntityID entity2)
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

bool CollisionSystem::checkSphereCollision(EntityID entity1, EntityID entity2)
{
    ch::Transform transform1;
    ch::Collision collision1;
    ch::Transform transform2;
    ch::Collision collision2;

    mWorld->unpack(entity1, transform1, collision1);
    mWorld->unpack(entity2, transform2, collision2);

    if ((transform1().mLocation - transform2().mLocation).length() <= collision1().mRadius + collision2().mRadius)
        return true;
    else
        return false;
}

void CollisionSystem::checkTerrainCollision(EntityID entity)
{
    ch::Transform transform;
    mWorld->unpack(entity, transform);
    ch::Terrain terrain;
    mWorld->unpack(mWorld->getEntity("mathTerrain"), terrain);

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
