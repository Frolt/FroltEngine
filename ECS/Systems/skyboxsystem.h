#ifndef SKYBOXSYSTEM_H
#define SKYBOXSYSTEM_H

#include "ECS/system.h"
#include <QOpenGLFunctions_4_1_Core>

class SkyboxSystem : public System, protected QOpenGLFunctions_4_1_Core
{
public:
    SkyboxSystem();
    void beginPlay() override;
    void update(float deltaTime) override;

private:
    void updateCubemapUniform(const SkyboxComponent &skybox, const MeshComponent &mesh);
};

#endif // SKYBOXSYSTEM_H
