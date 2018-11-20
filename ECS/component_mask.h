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

    template<typename T>
    void addComponent();
    template<typename T>
    void removeCompoent();

private:
    std::bitset<64> mMask;
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

#include "ECS/component.h"

template<typename T>
void ComponentMask::addComponent()
{
    mMask.set(T::family());
}

template<typename T>
void ComponentMask::removeCompoent()
{
    mMask.reset(T::family());
}


#endif // COMPONENT_MASK_H
