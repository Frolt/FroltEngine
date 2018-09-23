#ifndef ENTITY_H
#define ENTITY_H

#include <string>

struct Entity
{
    Entity(){};
    Entity(unsigned int ID, std::string name) : mID{ID}, mName{name} {};
    bool operator==(const Entity &rhs) { return mID == rhs.mID; }

    unsigned int mID;
    std::string mName;
};

#endif // ENTITY_H
