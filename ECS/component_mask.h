#ifndef COMPONENT_MASK_H
#define COMPONENT_MASK_H

#include <bitset>

struct ComponentMask
{
    bool isNewMatch(ComponentMask oldMask, ComponentMask systemMask) const;
    bool noLongerMatched(ComponentMask oldMask, ComponentMask systemMask) const;
    bool matches(ComponentMask other) const;
    const std::bitset<64> &getMask() const;
    void reset();

    template<typename ComponentType>
    void addComponent();
    template<typename ComponentType>
    void removeCompoent();

private:
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
