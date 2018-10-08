#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "ECS/component.h"
#include <Qt>
#include "a_math.h"

// Forward declarations
struct InputState;

struct InputComponent : public Component<InputComponent>
{
    InputComponent() = default;
    InputComponent(InputState *inputState);

    // Helper functions
    bool keyPressed(Qt::Key key) const;
    bool mousePressed(Qt::MouseButton button) const;
    am::Vec2 mousePos() const;
    QPoint wheelAngleDelta() const;
    QPoint wheelPixelDelta() const;

    // Data
    InputState *mInputState;
};

#endif // INPUTCOMPONENT_H
