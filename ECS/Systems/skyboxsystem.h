#ifndef SKYBOXSYSTEM_H
#define SKYBOXSYSTEM_H

#include "ECS/system.h"
#include <QOpenGLFunctions_4_1_Core>


/**
   @brief The SkyboxSystem class creates a skybox that follows the active camera.
   It uses a cubemap to create the skybox.
 */
class SkyboxSystem : public System, protected QOpenGLFunctions_4_1_Core
{
public:
    SkyboxSystem();
    void beginPlay() override;
    void update(float deltaTime) override;

private:
    void drawCubemap(const SkyboxComponent &skybox, const MeshComponent &mesh);
};

#endif // SKYBOXSYSTEM_H
