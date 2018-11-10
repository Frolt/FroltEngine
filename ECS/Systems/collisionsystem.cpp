#include "collisionsystem.h"

CollisionSystem::CollisionSystem()
{
    mSystemMask.addComponent<CollisionComponent>();
}

void CollisionSystem::beginPlay()
{

}

void CollisionSystem::update(float)
{
    for (auto &entity : mRegisteredEntities) {
        if (entity.mName != "player") {
            checkCollision(mWorld->getEntity("player"), entity);
        }
    }
}

void CollisionSystem::checkTerrainCollision(TransformComponent &transform)
{

}

bool CollisionSystem::checkCollision(Entity player, Entity trophy)
{
    ch::Transform transform;
    ch::Collision collision;

    mWorld->unpack(player, transform, collision);
    auto aPos = transform().mPosition;
    auto aSize = collision().mSize;
    aPos.x -= aSize.x;
    aPos.y += aSize.y;
    aPos.z -= aSize.z;

    mWorld->unpack(trophy, transform, collision);
    auto bPos = transform().mPosition;
    auto bSize = collision().mSize;
    bPos.x -= bSize.x;
    bPos.y += bSize.y;
    bPos.z -= bSize.z;

    aSize *= 2.0f;
    bSize *= 2.0f;

    bool collisionX = (aPos.x + aSize.x >= bPos.x) && (bPos.x + bSize.x >= aPos.x);
    bool collisionY = (aPos.y >= bPos.y - bSize.y) && (bPos.y >= aPos.y - aSize.y);
    bool collisionZ = (aPos.z + aSize.z >= bPos.z) && (bPos.z + bSize.z >= aPos.z);

    if (collisionX && collisionY && collisionZ) {
        if (trophy.mName == "AISphere") {
            ch::Material material;
            mWorld->unpack(player, transform, material);
            material().mDiffuseColor = Color::black;
            transform().mPosition = am::up() * 1000.0f;
        } else {
            mWorld->destroyEntity(trophy);
        }
    }

    return collisionX && collisionY && collisionZ;
}
