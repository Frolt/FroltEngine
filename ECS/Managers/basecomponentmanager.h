#ifndef BASECOMPONENTMANAGER_H
#define BASECOMPONENTMANAGER_H

class BaseComponentManager
{
public:
    BaseComponentManager();
    virtual ~BaseComponentManager();
    BaseComponentManager(const BaseComponentManager &other) = default;
    BaseComponentManager(BaseComponentManager &&other) = default;
    BaseComponentManager &operator=(const BaseComponentManager &other) = default;
    BaseComponentManager &operator=(BaseComponentManager &&other) = default;
};

#endif // BASECOMPONENTMANAGER_H
