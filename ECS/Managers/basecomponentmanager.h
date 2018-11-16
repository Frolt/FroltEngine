#ifndef BASECOMPONENTMANAGER_H
#define BASECOMPONENTMANAGER_H

#include "ECS/entity.h"

class BaseComponentManager
{
public:
    BaseComponentManager() = default;

    virtual void destroyComponent(Entity *entity) = 0;
};

#endif // BASECOMPONENTMANAGER_H
