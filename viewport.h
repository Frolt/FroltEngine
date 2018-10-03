#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QWindow>
#include <QOpenGLFunctions_4_1_Core>
#include <QSet>
#include "inputstate.h"
#include "meshfarm.h"
#include <memory>
#include "a_math.h"
#include "vertex.h"
#include "shader.h"
#include "paths.h"

// Forward declarations
class MainWindow;
class QOpenGLContext;
class QOpenGLDebugLogger;
class InputComponent;

class Viewport : public QWindow, protected QOpenGLFunctions_4_1_Core
{
    Q_OBJECT
public:
    Viewport(const QSurfaceFormat &format);
    ~Viewport() override;
    void initialize();
    void preRender();
    void postRender();

    // Event handlers
    virtual void exposeEvent(QExposeEvent *) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;

signals:
    void ready();

private:
    QOpenGLContext *mContext{nullptr};
    QOpenGLDebugLogger *mOpenGLDebugLogger{nullptr};
    bool mInitialized{false};
public:
    InputState mInputState;
    float mAspect{0.0f};
};

#endif // VIEWPORT_H
