#ifndef SYSTEM_H
#define SYSTEM_H

#include "entity.h"
#include <vector>
#include <bitset>

// Forward declarations
class World;

class System
{
public:
    System();
    virtual void init();
    virtual void update(float deltaTime);
    virtual void render();
    // Add a reference to the parent world
    void registerWorld(World *world);
    // This entity fits our current requirements
    void registerEntity(Entity entity);
    // This entity has stopped fitting our current requirements
    void deRegisterEntity(Entity entity);

protected:
    // Specifies which components our system cares about — its size should = the number of different components
    std::bitset<32> mSystemSignature;
    // These entities fit the systemSignature and should be iterated upon for any functionality
    std::vector<Entity> mRegisteredEntities;
    World *mWorld;
};

#endif // SYSTEM_H
