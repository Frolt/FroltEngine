#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include "inputcomponent.h"

class PlayerInputComponent : public InputComponent
{
public:
    PlayerInputComponent(const InputState *inputState);
    virtual ~PlayerInputComponent() override;
    virtual void beginPlay() override;
    virtual void update(float deltaTime) override;
};

#endif // PLAYERINPUTCOMPONENT_H
