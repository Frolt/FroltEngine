#include "inputcomponent.h"
#include "inputstate.h"

InputComponent::InputComponent(InputState *inputState)
    :mInputState{inputState}
{

}

bool InputComponent::keyPressed(Qt::Key key) const
{
    if (mInputState->mPressedKeys.contains(key))
        return true;
    return false;
}

bool InputComponent::mousePressed(Qt::MouseButton button) const
{
    if (mInputState->mPressedMouseButtons.contains(button))
        return true;
    return false;
}

am::Vec2 InputComponent::mousePos() const
{
    return mInputState->mMousePos;
}

QPoint InputComponent::wheelAngleDelta() const
{
    return mInputState->mWheelAngleDelta;
}

QPoint InputComponent::wheelPixelDelta() const
{
    return mInputState->mWheelPixelDelta;
}
