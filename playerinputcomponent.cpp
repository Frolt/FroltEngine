#include "playerinputcomponent.h"
#include <QDebug>
#include "viewport.h"

PlayerInputComponent::PlayerInputComponent(Viewport *viewport)
    : InputComponent (viewport)
{

}

PlayerInputComponent::~PlayerInputComponent()
{

}

void PlayerInputComponent::update()
{
    for (auto i = mViewport->mPressedKeys.begin(); i != mViewport->mPressedKeys.end(); i++) {
        switch (*i) {
        case Qt::Key_W:
            qDebug() << "W";
            break;
        case Qt::Key_A:
            qDebug() << "A";
            break;
        case Qt::Key_S:
            qDebug() << "S";
            break;
        case Qt::Key_D:
            qDebug() << "D";
            break;
        }
    }
}
