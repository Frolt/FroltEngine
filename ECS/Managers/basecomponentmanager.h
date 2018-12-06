#ifndef BASECOMPONENTMANAGER_H
#define BASECOMPONENTMANAGER_H

#include "ECS/entity.h"


/**
   @brief The BaseComponentManager class is an interface class for all component managers.
   This is primarily used to store all the managers inside a single vector in the World class.
 */
class BaseComponentManager
{
public:
    virtual ~BaseComponentManager() = default;
    /// used to destroy components in a non optimized, lazy way
    virtual void destroyComponent(EntityID entity) = 0;
};

#endif // BASECOMPONENTMANAGER_H
