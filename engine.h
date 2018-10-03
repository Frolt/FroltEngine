#ifndef ENGINE_H
#define ENGINE_H

#include <QElapsedTimer>
#include <QObject>
#include <memory>
#include <vector>
#include "shader.h"
#include "vertex.h"
#include <QOpenGLFunctions_4_1_Core>

// Forward declarations
class QTimer;
class Viewport;
class World;
class MeshFarm;

class Engine : public QObject, protected QOpenGLFunctions_4_1_Core
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

public:
    Viewport *mViewport;
    float mDeltaTime{0.0f};
    // Worlds
    std::unique_ptr<World> mWorld;
    // Farms
    std::unique_ptr<MeshFarm> mMeshFarm;
    // Shaders
    std::unique_ptr<Shader> mPhongShader;
private:
    // Timers
    QElapsedTimer mTimer;
    QElapsedTimer mTickTimer;
    QTimer *mGameLoopTimer;
};

#endif // ENGINE_H
