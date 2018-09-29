#ifndef ENTITY_H
#define ENTITY_H

#include <string>

struct Entity
{
    Entity();
    Entity(unsigned int ID, std::string name);
    bool operator==(const Entity &rhs);
    friend bool operator<(const Entity &lhs, const Entity &rhs);

    // Variables
    unsigned int mID = 0;
    std::string mName;
};

#endif // ENTITY_H
