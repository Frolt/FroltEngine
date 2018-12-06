#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H

#include "ECS/system.h"


// Forward declarations
struct CollisionEvent;

/**
   @brief The CombatSystem class implements combat logic.
   It does not pay attention to entities, but rather CollisionEvents.
 */
class CombatSystem : public System
{
public:
    CombatSystem();

    void beginPlay() override;
    void update(float deltaTime) override;

    void onCollisionEvent(CollisionEvent *event);
    void onSphereCollisionEvent(SphereCollisionEvent *event);
};

#endif // COMBATSYSTEM_H
