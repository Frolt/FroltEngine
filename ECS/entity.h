#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <functional>

/// Type alias for entity ID
using EntityID = unsigned int;

struct Entity
{
    Entity();
    Entity(unsigned int ID, const std::string &name);

    bool operator==(const Entity &rhs) const;
    bool operator<(const Entity &rhs) const;
    operator EntityID();

    // Variables
    unsigned int mID{0};
    std::string mName;
    Entity *mParent{nullptr};
    Entity *mChild{nullptr};
};

// Define hash function for Entity
namespace std {
    template <>
    struct hash<Entity>
    {
        std::size_t operator()(const Entity &key) const
        {
            return std::hash<unsigned int>{}(key.mID);
//            auto h1 = std::hash<std::string>{}(key.mName);
//            auto h2 = std::hash<unsigned int>{}(key.mID);
//            return h1 ^ h2 << 1;
        }
    };
}

#endif // ENTITY_H
