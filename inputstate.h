#ifndef INPUTSTATE_H
#define INPUTSTATE_H

#include <QSet>
#include <QHash>
#include "a_math.h"

struct InputState
{
    // TODO Qhash?
    QSet<int> mPressedKeys;
    QSet<int> mPressedMouseButtons;
    am::Vec2 mMousePos;
    Qt::MouseEventFlags mDoubleClick;
    QPoint mWheelAngleDelta;
    QPoint mWheelPixelDelta;
};

#endif // INPUTSTATE_H
