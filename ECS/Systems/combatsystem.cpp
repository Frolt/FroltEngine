#include "combatsystem.h"
#include "EventSystem/collisionevent.h"

CombatSystem::CombatSystem()
{

}

void CombatSystem::beginPlay()
{
//    mEventBus->subscribe(this, &CombatSystem::onCollisionEvent);
}

void CombatSystem::update(float deltaTime)
{

}

void CombatSystem::onCollisionEvent(CollisionEvent *event)
{
    // TODO make gameplay logic when entities collide
    // WHAT HAPPENS HERE!!?!?=!
    qDebug() << "A collision event happened!!";
}
