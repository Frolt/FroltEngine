#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <functional>

/// Type alias for entity ID
using EntityID = unsigned int;

/**
   @brief The Entity struct keeps an unsigned int ID, a name, and a parent/child pointer.
   An entity is referenced by the ID only throughout the system.
    The only place the full Entity class is stored is inside the EntityManager
 */
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
    /// Define hash function for Entity
    struct hash<Entity>
    {
        std::size_t operator()(const Entity &key) const
        {
            return std::hash<unsigned int>{}(key.mID);
        }
    };
}

#endif // ENTITY_H
