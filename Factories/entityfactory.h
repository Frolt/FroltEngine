#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <string>
#include "a_math.h"


// Forward declarations
struct EntityHandle;
struct InputState;
class MaterialFactory;
class MeshFactory;
class World;
class Shader;
class Engine;

/**
   @brief The EntityFactory class is used to create predefined entities
 */
class EntityFactory
{
public:
    EntityFactory(MeshFactory &meshFactory, MaterialFactory &materialFactory, World &world, InputState &inputState, Shader &shader);

    // Lights
    EntityHandle createDirectionalLight(const std::string &name, const am::Vec3 &color = Color::white);
    EntityHandle createPointLight(const std::string &name, const am::Vec3 &location = {0}, const am::Vec3 &color = Color::white);
    EntityHandle createSpotlight(const std::string &name, const am::Vec3 &location = {0}, const am::Vec3 &dir = -am::up(), const am::Vec3 &color = Color::white);
    // Meshes
    EntityHandle createCube(const std::string &name, const am::Vec3 &color = Color::orangeRed, const am::Vec3 &location = {0});
    EntityHandle createSphere(const std::string &name, const am::Vec3 &color = Color::orangeRed, const am::Vec3 &location = {0});
    EntityHandle createCrystal(const std::string &name, const am::Vec3 &color = Color::orangeRed, const am::Vec3 &location = {0});
    EntityHandle createModel(const std::string &name, const std::string &path, const am::Vec3 &location = {0});
    // Player
    EntityHandle createPlayerCube(const std::string &name, const am::Vec3 &color = Color::orangeRed, const am::Vec3 &location = {0});
    EntityHandle createPlayerSphere(const std::string &name, const am::Vec3 &color = Color::orangeRed, const am::Vec3 &location = {0});
    EntityHandle createPlayerModel(const std::string &name, const am::Vec3 &color = Color::orangeRed, const am::Vec3 &location = {0});
    // Cameras
    EntityHandle createFreeCamera(const std::string &name, const am::Vec3 &location = {0});
    // Terrain
    EntityHandle createMathTerrain(const std::string &name, const am::Vec3 &color = Color::green, int min = -100, int max = 100, const am::Vec3 &location = {0});
    EntityHandle createLasTerrain(const std::string &name, const am::Vec3 &color = Color::green, const am::Vec3 &location = {0});
    // Testing
    EntityHandle createTestTriangle(const std::string &name, const am::Vec3 &color = Color::green, const am::Vec3 &location = {0});
    EntityHandle createPhysicsBall(const std::string &name, const am::Vec3 &color = Color::green, const am::Vec3 &location = {0});
    // AI
    EntityHandle createAISphere(const std::string &name, const am::Vec3 &color = Color::green, const am::Vec3 &location = {0});
    EntityHandle createAIShark(const std::string &name , const std::string &path, const am::Vec3 &color = Color::green, const am::Vec3 &location = {0});
    // Skybox
    EntityHandle createSkybox(const std::string &name , const std::string &skyType, const am::Vec3 &location = {0});

private:
    MeshFactory &mMeshFactory;
    MaterialFactory &mMaterialFactory;
    World &mWorld;
    InputState &mInputState;
    Shader &mDefaultShader;
};

#endif // ENTITYFACTORY_H
