#ifndef COMPONENT_MASK_H
#define COMPONENT_MASK_H

#include <bitset>

struct ComponentMask
{
public:
    ComponentMask();
    bool isNewMatch(ComponentMask oldMask, ComponentMask systemMask);
    bool noLongerMatched(ComponentMask oldMask, ComponentMask systemMask);
    bool matches(ComponentMask other);

    template<typename T>
    void addComponent();
    template<typename T>
    void removeCompoent();

private:
    std::bitset<32> mMask;
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

#include "ECS/component.h"

template<typename T>
void ComponentMask::addComponent()
{
    mMask.set(Component<T>::typeID());
}

template<typename T>
void ComponentMask::removeCompoent()
{
    mMask.reset(Component<T>::typeID());
}


#endif // COMPONENT_MASK_H
