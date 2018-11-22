#ifndef INPUTSTATE_H
#define INPUTSTATE_H

#include <QSet>
#include <QHash>
#include "a_math.h"

/**
   @brief The InputState struct stores the input states from the viewport class.
 */
struct InputState
{
    QSet<int> mPressedKeys;
    QSet<int> mPressedMouseButtons;
    am::Vec2 mMousePos;
    QPoint mWheelAngleDelta;
    QPoint mWheelPixelDelta;
};

#endif // INPUTSTATE_H
