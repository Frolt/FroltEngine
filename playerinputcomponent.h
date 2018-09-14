#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include "inputcomponent.h"

class PlayerInputComponent : public InputComponent
{
public:
    PlayerInputComponent(Viewport *viewport);
    virtual ~PlayerInputComponent() override;
    virtual void update() override;
};

#endif // PLAYERINPUTCOMPONENT_H
