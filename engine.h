#ifndef ENGINE_H
#define ENGINE_H

#include <QElapsedTimer>
#include <QObject>
#include <memory>
#include <vector>

// Forward declarations
class QTimer;
class Viewport;
class World;

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
    // Timers
    QElapsedTimer mTimer;
    QElapsedTimer mTickTimer;
    QTimer *mGameLoopTimer;
    // Pointers
    Viewport *mViewport;
    // Variables
    float mDeltaTime{0.0f};
    bool mIsRunning{true};
    // Worlds
    std::unique_ptr<World> mWorld;
};

#endif // ENGINE_H
