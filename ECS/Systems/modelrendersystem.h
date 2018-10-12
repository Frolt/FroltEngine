#ifndef MODELRENDERSYSTEM_H
#define MODELRENDERSYSTEM_H

#include <QOpenGLFunctions_4_1_Core>
#include "ECS/system.h"

class modelRenderSystem : public System, protected QOpenGLFunctions_4_1_Core
{
public:
    modelRenderSystem();

    void beginPlay() override;
    void update(float deltaTime) override;
    void updateMaterialUniforms(const Shader shader, const MaterialComponent &material) const;
    void updateTransformUniforms(const Shader shader, const TransformComponent &transform) const;
    void draw(ModelComponent &model);
};

#endif // MODELRENDERSYSTEM_H
