#ifndef BASECOMPONENTMANAGER_H
#define BASECOMPONENTMANAGER_H

#include "ECS/entity.h"

class BaseComponentManager
{
public:
    BaseComponentManager() = default;
    virtual ~BaseComponentManager();
    BaseComponentManager(const BaseComponentManager &other) = default;
    BaseComponentManager(BaseComponentManager &&other) = default;
    BaseComponentManager &operator=(const BaseComponentManager &other) = default;
    BaseComponentManager &operator=(BaseComponentManager &&other) = default;

    virtual void destroyComponent(const Entity &entity) = 0;
};

#endif // BASECOMPONENTMANAGER_H
