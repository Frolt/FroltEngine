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
    // TODO make gameplay logic when entities collide
    qDebug() << "A collision event happened!!";
    qDebug() << "WORKING!!!!";
}
