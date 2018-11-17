#include "combatsystem.h"
#include "EventSystem/collisionevent.h"

CombatSystem::CombatSystem()
{

}

void CombatSystem::beginPlay()
{
    mEventBus->subscribe(this, &CombatSystem::onCollisionEvent);
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
    if (other == mWorld->getEntity("AISphere")) {
        ch::Material material;
        mWorld->unpack(player, transform, material);
        material().mDiffuseColor = Color::black;
        transform().mPosition = am::up() * 1000.0f;
    } else {
        mWorld->destroyEntity(other);
    }
}
