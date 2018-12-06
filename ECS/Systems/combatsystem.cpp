#include "combatsystem.h"
#include "EventSystem/collisionevent.h"
#include "engine.h"


CombatSystem::CombatSystem()
{

}

void CombatSystem::beginPlay()
{
    mEventHandler->subscribe(this, &CombatSystem::onCollisionEvent);
    mEventHandler->subscribe(this, &CombatSystem::onSphereCollisionEvent);
}

void CombatSystem::update(float)
{

}

void CombatSystem::onCollisionEvent(CollisionEvent *event)
{
    auto player = event->mEntityA;
    auto other = event->mEntityB;
    ch::Transform transform;

    // If we hit the AI guard
    if (mWorld->hasComponent<AIComponent>(other)) {
        if (mWorld->hasComponent<PlayerComponent>(player)) {
            ch::Player playerComp;
            ch::Material material;
            mWorld->unpack(player, transform, material, playerComp);
            material().mDiffuseColor = Color::black;
            material().mHasDiffMap = false;
            playerComp().isDead = true;
            qWarning("YOU DIED!");
        }
    } else if (!mWorld->hasComponent<PlayerComponent>(other) &&
               !mWorld->hasComponent<AIComponent>(other)) {
        mWorld->destroyEntity(other);
        if (!mWorld->hasComponent<PlayerComponent>(player)) {
            ch::Material material;
            mWorld->unpack(player, material);
            material().mHasDiffMap = false;
            material().mDiffuseColor = Color::orangeRed;
        }
    }
}

void CombatSystem::onSphereCollisionEvent(SphereCollisionEvent *event)
{
    // Implement proper sphere collision response
    ch::Movement movement1;
    ch::Transform transform1;
    ch::Movement movement2;
    ch::Transform transform2;
    mWorld->unpack(event->mEntityA, movement1, transform1);
    mWorld->unpack(event->mEntityB, movement2, transform2);

    // Push back sphere
    transform1().mLocation += movement2().mVelocity * mWorld->mEngine.mDeltaTime;
    transform2().mLocation += movement1().mVelocity * mWorld->mEngine.mDeltaTime;

    // Swap velocity vectors
    auto tempVel = movement1().mVelocity;
    movement1().mVelocity = movement2().mVelocity;
    movement2().mVelocity = tempVel;
}
