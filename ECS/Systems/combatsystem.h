#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H

#include "ECS/system.h"

// Forward declarations
struct CollisionEvent;

class CombatSystem : public System
{
public:
    CombatSystem();

    void beginPlay() override;
    void update(float deltaTime) override;

    void onCollisionEvent(CollisionEvent *event);
};

#endif // COMBATSYSTEM_H
