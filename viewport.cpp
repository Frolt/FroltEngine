#include "viewport.h"
#include <QOpenGLContext>
#include <QOpenGLDebugLogger>
#include <QCoreApplication>
#include <QKeyEvent>
#include <QMouseEvent>

Viewport::Viewport(const QSurfaceFormat &format)
{
    // TODO clean up
    setSurfaceType(QSurface::OpenGLSurface);
    setFormat(format);
    mContext = new QOpenGLContext(this);
    mContext->setFormat(requestedFormat());
    mContext->create();
}

Viewport::~Viewport()
{

}

void Viewport::initialize()
{
    qDebug() << "initialize() called";

    mContext->makeCurrent(this);
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

    mInitialized = true;
    emit ready();
}

void Viewport::preRender()
{
    mContext->makeCurrent(this);
    initializeOpenGLFunctions();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Viewport::postRender()
{
    mContext->swapBuffers(this);
}

void Viewport::exposeEvent(QExposeEvent *)
{
    qDebug() << "exposeEvent() called";

    if (!mInitialized)
        initialize();

    const int retinaScale = static_cast<int>(devicePixelRatio());
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);
    mAspect = static_cast<float>(width()) / static_cast<float>(height());
}

void Viewport::keyPressEvent(QKeyEvent *event)
{
    mInputState.mPressedKeys += event->key();
}

void Viewport::keyReleaseEvent(QKeyEvent *event)
{
    mInputState.mPressedKeys -= event->key();
}

void Viewport::mouseDoubleClickEvent(QMouseEvent *event)
{
    mInputState.mDoubleClick = event->flags();
}

void Viewport::mouseMoveEvent(QMouseEvent *event)
{
    mInputState.mMousePos.x = event->pos().x();
    mInputState.mMousePos.y = event->pos().y();
}

void Viewport::mousePressEvent(QMouseEvent *event)
{
    mInputState.mPressedMouseButtons += event->button();
    mInputState.mDoubleClick = event->flags();
}

void Viewport::mouseReleaseEvent(QMouseEvent *event)
{
    mInputState.mPressedMouseButtons -= event->button();
    mInputState.mDoubleClick = event->flags();
}

void Viewport::wheelEvent(QWheelEvent *event)
{
    mInputState.mWheelAngleDelta += event->angleDelta();
    mInputState.mWheelPixelDelta += event->pixelDelta();
}
