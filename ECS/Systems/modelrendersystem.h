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
    void updateMaterialUniforms(Shader shader, MaterialComponent &material);
    void updateTransformUniforms(Shader shader, const TransformComponent &transform) const;
    void draw(ModelComponent &model);
};

#endif // MODELRENDERSYSTEM_H
