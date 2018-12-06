#ifndef COMPONENT_MASK_H
#define COMPONENT_MASK_H

#include <bitset>


/**
   @brief The ComponentMask struct stores a bitmask to represent each component.
   Each bit represent a specific componentType.

   This is used to update the entities each systems should pay attention too,
   and to specify what components a system requires
 */
struct ComponentMask
{
    /// Check if the new entity mask matches the system mask
    bool isNewMatch(ComponentMask oldMask, ComponentMask systemMask) const;
    /// Check if the new entity mask no longer matches the system mask
    bool noLongerMatched(ComponentMask oldMask, ComponentMask systemMask) const;
    /// Sets all the bits to 0/false
    void reset();
    /// The bit that represent the ComponentType will be set to 1
    template<typename ComponentType>
    void addComponent();
    /// The bit that represent the ComponentType will be set to 0
    template<typename ComponentType>
    void removeCompoent();

private:
    /// Simply check if mMask matches other through a bitwise AND operator
    bool matches(ComponentMask other) const;
    const std::bitset<64> &getMask() const;

private:
    /// Can support 64 components
    std::bitset<64> mMask;
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

#include "ECS/component.h"

template<typename ComponentType>
void ComponentMask::addComponent()
{
    mMask.set(ComponentType::family());
}

template<typename ComponentType>
void ComponentMask::removeCompoent()
{
    mMask.reset(ComponentType::family());
}


#endif // COMPONENT_MASK_H
