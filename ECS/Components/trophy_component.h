#ifndef TROPHY_COMPONENT_H
#define TROPHY_COMPONENT_H

#include "ECS/component.h"

struct TrophyComponent : public Component<TrophyComponent>
{
    TrophyComponent();

    bool mActive{true};
};

#endif // TROPHY_COMPONENT_H
