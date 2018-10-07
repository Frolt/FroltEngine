#include "entity.h"


Entity::Entity(unsigned int ID, const std::string &name)
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
