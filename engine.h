#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QOpenGLFunctions_4_1_Core>
#include <QElapsedTimer>
#include <memory>
#include <vector>
#include "shader.h"
#include "ECS/Handles/entityhandle.h"

// Forward declarations
class QTimer;
class Viewport;
class World;
class MeshFactory;
class EntityFactory;
class MaterialFactory;
class EventHandler;

/**
   @brief The Engine class is the owner of the World class instance,
    the main shader, the eventHandler, and all the factories
    It also provides general utility functions like getTime()

    The engine handles all timers aswell as the main game loop.
    The game scene is created inside the initialize method
 */
class Engine : public QObject, protected QOpenGLFunctions_4_1_Core
{
    Q_OBJECT
public:
    explicit Engine(Viewport *viewport, QObject *parent = nullptr);

    /**
       @brief initialize the engine variables and creates the game scene
     */
    void initialize();
    /// Starts the main game loop with a timer when the QT event system is ready
    void startGameLoop();
    /// gives the elapsed gametime in seconds
    float getTime();

private slots:
    /**
       @brief This is the main game loop, it calculates the deltaTime
        and calls the update function for all the systems
     */
    void gameLoop();

public:
    Viewport *mViewport;
    float mDeltaTime{0.0f};
    // Worlds
    std::unique_ptr<World> mWorld;
    // Factories
    std::unique_ptr<MeshFactory> mMeshFactory;
    std::unique_ptr<MaterialFactory> mMaterialFactory;
    std::unique_ptr<EntityFactory> mEntityFactory;
    // EventHandler
    std::unique_ptr<EventHandler> mEventHandler;
    /// This is the main/only shader the engine use
    Shader mPhongShader;
    Shader mSkyboxShader;
    // Trophies
    std::vector<EntityHandle> mTrophies;
private:
    /// Timer to calculate elapsed time since game start
    QElapsedTimer mTimer;
    /// Timer to calculate deltaTime
    QElapsedTimer mTickTimer;
    /// Timer to drive the gameloop
    QTimer *mGameLoopTimer;
};

#endif // ENGINE_H
