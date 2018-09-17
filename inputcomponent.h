#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "component.h"

// Forward declarations
class Viewport;
struct InputState;

class InputComponent : public Component
{
public:
    InputComponent(const InputState *inputState);

protected:
    const InputState *mInputState;
};

#endif // INPUTCOMPONENT_H
