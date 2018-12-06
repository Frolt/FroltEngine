#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <functional>


/// Type alias for entity ID
using EntityID = size_t;

/**
   @brief The Entity struct keeps an unsigned int ID, a name, and a parent/child pointer.
   An entity is referenced by the ID only throughout the system.
    The only place the full Entity class is stored is inside the EntityManager
 */
struct Entity
{
    Entity();
    Entity(size_t ID, const std::string &name);

    bool operator==(const Entity &rhs) const;
    bool operator<(const Entity &rhs) const;
    operator EntityID();

    // Variables
    size_t mID{0};
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
            return std::hash<size_t>{}(key.mID);
        }
    };
}

#endif // ENTITY_H
