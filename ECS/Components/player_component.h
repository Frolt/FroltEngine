#ifndef PLAYER_COMPONENT_H
#define PLAYER_COMPONENT_H

#include "ECS/component.h"


struct PlayerComponent : public Component<PlayerComponent>
{
    bool isDead{false};
};

#endif // PLAYER_COMPONENT_H
