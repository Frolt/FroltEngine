#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <bitset>
#include "entity.h"
#include "ECS/component_mask.h"

// Forward declarations
class World;

class System
{
public:
    System() = default;
    virtual ~System();
    virtual void beginPlay();
    virtual void update(float deltaTime);

    void setWorld(World *world);
    void registerEntity(const Entity &entity);
    void deRegisterEntity(const Entity &entity);

public:
    ComponentMask mSystemMask;
protected:
    // TODO vector has slow search O(n)
    // bad when ComponentMask uses deRegisterEntity() method
    // but vector is good for iterating
    std::vector<Entity> mRegisteredEntities;
    World *mWorld;
};

#endif // SYSTEM_H
