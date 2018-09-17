#ifndef COMPONENT_H
#define COMPONENT_H

#include "enums.h"

// Forward declarations
class GameObject;

class Component
{
public:
    virtual ~Component();
    virtual void beginPlay();
    virtual void update(float deltaTime);

public:
    GameObject *mOwner{nullptr};
    COMPONENT mType{COMPONENT::NO_VALUE};
};

#endif // COMPONENT_H
