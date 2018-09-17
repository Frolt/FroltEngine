#ifndef INPUTSTATE_H
#define INPUTSTATE_H

#include <QSet>
#include "a_math.h"

struct InputState
{
    QSet<int> mPressedKeys;
    QSet<int> mPressedMouseButtons;
    am::Vec2 mMousePos;
    Qt::MouseEventFlags mDoubleClick;
    QPoint mWheelAngleDelta;
    QPoint mWheelPixelDelta;
};

#endif // INPUTSTATE_H
