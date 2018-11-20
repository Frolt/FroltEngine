#ifndef COMPONENT_H
#define COMPONENT_H

#include <utility>

// Counter wrapper
struct FamilyCounter {
    static unsigned int ID;
};

// Interface for components
template<typename ComponentType>
struct Component
{
protected:
    Component() = default;
    virtual ~Component() = default;
public:
    static unsigned int family();
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

template<typename ComponentType>
unsigned int Component<ComponentType>::family()
{
    // id will only initialize once
    static unsigned int ID = FamilyCounter::ID++;
    return ID;
}

#endif // COMPONENT_H
