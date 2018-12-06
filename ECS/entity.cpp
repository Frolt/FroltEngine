#include "entity.h"


Entity::Entity()
{

}

Entity::Entity(size_t ID, const std::string &name)
    : mID{ID}, mName{name}
{

}

bool Entity::operator==(const Entity &rhs) const
{
    return mID == rhs.mID;
}

bool Entity::operator<(const Entity &rhs) const
{
    return (mID < rhs.mID);
}

Entity::operator EntityID()
{
    return mID;
}
