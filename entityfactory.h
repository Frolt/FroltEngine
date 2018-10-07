#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <string>
#include "a_math.h"

// Forward declarations
struct EntityHandle;
class MeshFactory;
class World;
class Shader;

class EntityFactory
{
public:
    EntityFactory(MeshFactory &meshFactory, World &world, Shader &shader);

    // Lights
    EntityHandle createDirectionalLight(const std::string &name, const am::Vec3 &color = Colors::white);
    EntityHandle createPointLight(const std::string &name, const am::Vec3 &pos = {0}, const am::Vec3 &color = Colors::white);
    EntityHandle createSpotlight(const std::string &name, const am::Vec3 &pos = {0}, const am::Vec3 &color = Colors::white);
    // Meshes
    EntityHandle createCube(const std::string &name, const am::Vec3 &color = Colors::orangeRed, const am::Vec3 &pos = {0});
    EntityHandle createSphere(const std::string &name, const am::Vec3 &color = Colors::orangeRed, const am::Vec3 &pos = {0});
    // Player
    EntityHandle createPlayerCube(const std::string &name, const am::Vec3 &color = Colors::orangeRed, const am::Vec3 &pos = {0});
    EntityHandle createPlayerSphere(const std::string &name, const am::Vec3 &color = Colors::orangeRed, const am::Vec3 &pos = {0});
    // AI
    EntityHandle createAICube(const std::string &name, const am::Vec3 &color = Colors::orangeRed, const am::Vec3 &pos = {0});
    EntityHandle createAISphere(const std::string &name, const am::Vec3 &color = Colors::orangeRed, const am::Vec3 &pos = {0});
    // Camera
    EntityHandle createCamera(const std::string &name, const am::Vec3 &pos = {0});
    // Terrain
    EntityHandle createLasTerrain(const std::string &name, const am::Vec3 &color = Colors::green, const am::Vec3 &pos = {0});
    EntityHandle createTerrain(const std::string &name, const am::Vec3 &color = Colors::green, const am::Vec3 &pos = {0});

private:
    MeshFactory &mMeshFactory;
    World &mWorld;
    Shader &mDefaultShader;
};

#endif // ENTITYFACTORY_H
