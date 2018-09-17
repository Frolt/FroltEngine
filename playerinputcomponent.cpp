#include "playerinputcomponent.h"
#include <QDebug>
#include "viewport.h"
#include "enums.h"
#include "gameobject.h"
#include "transformcomponent.h"

PlayerInputComponent::PlayerInputComponent(const InputState *inputState)
    : InputComponent (inputState)
{
    mType = COMPONENT::PLAYER_INPUT;
}

PlayerInputComponent::~PlayerInputComponent()
{

}

void PlayerInputComponent::beginPlay()
{
    if (auto tmp = mOwner->getComponent<TransformComponent>())
        qDebug() << tmp->mScale;
}

void PlayerInputComponent::update(float deltaTime)
{
    for (auto i = mInputState->mPressedKeys.begin(); i != mInputState->mPressedKeys.end(); i++) {
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

    for (auto i = mInputState->mPressedMouseButtons.begin(); i != mInputState->mPressedMouseButtons.end(); i++) {
        switch (*i) {
        case Qt::LeftButton:
            qDebug() << "left mouse btn";
            break;
        case Qt::RightButton:
            qDebug() << "right mouse btn";
            break;
        }
    }
}
