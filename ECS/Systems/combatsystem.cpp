#include "combatsystem.h"
#include "EventSystem/collisionevent.h"

CombatSystem::CombatSystem()
{

}

void CombatSystem::beginPlay()
{
    mEventHandler->subscribe(this, &CombatSystem::onCollisionEvent);
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
        ch::Material material;
        mWorld->unpack(player, transform, material);
        material().mDiffuseColor = Color::black;
        transform().mLocation = am::up() * 100.0f;
    } else {
        if (mWorld->hasComponent<AIComponent>(player)) {
//            ch::Ai ai;
//            mWorld->unpack(player, ai);
//            ai().mChase = true;
        }
        mWorld->destroyEntity(other);
    }
}
