#ifndef BASECOMPONENTMANAGER_H
#define BASECOMPONENTMANAGER_H

#include "ECS/entity.h"

class BaseComponentManager
{
public:
    virtual ~BaseComponentManager() = default;
    virtual void destroyComponent(EntityID entity) = 0;
};

#endif // BASECOMPONENTMANAGER_H
