#include "entity.h"


Entity::Entity()
{

}

Entity::Entity(unsigned int ID, std::string name)
    : mID{ID}, mName{name}
{

}

bool Entity::operator==(const Entity &rhs)
{
    return mID == rhs.mID;
}

bool operator<(const Entity &lhs, const Entity &rhs)
{
    return (lhs.mID < rhs.mID);
}
