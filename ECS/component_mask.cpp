#include "component_mask.h"

ComponentMask::ComponentMask()
{

}

bool ComponentMask::isNewMatch(ComponentMask oldMask, ComponentMask systemMask)
{
    return matches(systemMask) && !oldMask.matches(systemMask);
}

bool ComponentMask::noLongerMatched(ComponentMask oldMask, ComponentMask systemMask)
{
    return oldMask.matches(systemMask) && !matches(systemMask);
}

bool ComponentMask::matches(ComponentMask other)
{
    return (mMask & other.mMask) == other.mMask;
}
