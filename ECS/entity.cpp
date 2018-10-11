#include "entity.h"

Entity::Entity()
{

}

Entity::Entity(unsigned int ID, const std::string &name)
    : mID{ID}, mName{name}
{

}

Entity::~Entity()
{

}

Entity::Entity(const Entity &other)
    : mID{other.mID}, mName{other.mName}
{

}

Entity::Entity(Entity &&other)
    : mID{std::move(other.mID)}, mName{std::move(other.mName)}
{
}

Entity &Entity::operator=(const Entity &other)
{
    mID = other.mID;
    mName = other.mName;
    return *this;
}

Entity &Entity::operator=(Entity &&other)
{
    mID = std::move(other.mID);
    mName = std::move(other.mName);
    return *this;
}

bool Entity::operator==(const Entity &rhs) const
{
    return mID == rhs.mID;
}

bool Entity::operator<(const Entity &rhs) const
{
    return (mID < rhs.mID);
}
