#ifndef AI_COMPONENT_H
#define AI_COMPONENT_H

#include "ECS/component.h"


struct AIComponent : public Component<AIComponent>
{
    bool mIsChasing{false};
};

#endif // AI_COMPONENT_H
