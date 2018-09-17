#ifndef ENGINE_H
#define ENGINE_H

#include <QElapsedTimer>
#include <QObject>
#include <memory>
#include <vector>
#include "factory.h"

// Forward declarations
class GameObject;
class QTimer;
class Viewport;
class Component;

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(Viewport *viewport, QObject *parent = nullptr);

    void initialize();
    void startGameLoop();
    void render();
    float getTime();

private slots:
    void gameLoop();

private:
    std::vector<std::unique_ptr<GameObject>> mGameObjects;
    QElapsedTimer mTimer;
    QElapsedTimer mTickTimer;
    QTimer *mGameLoopTimer;
    Viewport *mViewport;
    float mDeltaTime{0.0f};
    bool mIsRunning{true};
};

#endif // ENGINE_H
