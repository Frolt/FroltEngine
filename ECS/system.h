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
    System();
    virtual ~System();
    virtual void beginPlay();
    virtual void update(float deltaTime);
    virtual void render();

    void setWorld(World *world);
    void registerEntity(Entity entity);
    void deRegisterEntity(Entity entity);

public:
    ComponentMask mSystemMask;
protected:
    std::vector<Entity> mRegisteredEntities;
    World *mWorld;
};

#endif // SYSTEM_H
