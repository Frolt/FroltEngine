#include "component_mask.h"


bool ComponentMask::isNewMatch(ComponentMask oldMask, ComponentMask systemMask) const
{
    return matches(systemMask) && !oldMask.matches(systemMask);
}

bool ComponentMask::noLongerMatched(ComponentMask oldMask, ComponentMask systemMask) const
{
    return oldMask.matches(systemMask) && !matches(systemMask);
}

bool ComponentMask::matches(ComponentMask other) const
{
    return (mMask & other.mMask) == other.mMask;
}

const std::bitset<64> &ComponentMask::getMask() const
{
    return mMask;
}

void ComponentMask::reset()
{
    mMask.reset();
}
