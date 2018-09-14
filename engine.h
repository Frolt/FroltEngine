#ifndef ENGINE_H
#define ENGINE_H

#include <QElapsedTimer>
#include <QObject>
#include <memory>
#include <vector>

// Forward declarations
class Entity;
class QTimer;
class Viewport;

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
    std::vector<std::shared_ptr<Entity>> mEntities;
    float mDeltaTime{0.0f};
    bool mIsRunning{true};
    QElapsedTimer mTimer;
    QElapsedTimer mTickTimer;
    QTimer *mGameLoopTimer;
    Viewport *mViewport;
};

#endif // ENGINE_H
