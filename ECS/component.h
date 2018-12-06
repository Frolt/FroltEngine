#ifndef COMPONENT_H
#define COMPONENT_H

#include <utility>


/// Simple counter to provide unique family ID
struct FamilyCounter {
    static unsigned int ID;
};

/**
   @brief The Component struct is an interface for all components.
   It also provide each new componentType with an unique family ID
 */
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
