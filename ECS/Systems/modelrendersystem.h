#ifndef MODELRENDERSYSTEM_H
#define MODELRENDERSYSTEM_H

#include <QOpenGLFunctions_4_1_Core>
#include "ECS/system.h"


/**
   @brief The modelRenderSystem class renders all entities with a model component to the viewport
 */
class ModelRenderSystem : public System, protected QOpenGLFunctions_4_1_Core
{
public:
    ModelRenderSystem();

    void beginPlay() override;
    void update(float deltaTime) override;
    void updateMaterialUniforms(const Shader shader, const MaterialComponent &material) const;
    void updateTransformUniforms(const Shader shader, EntityHandle entity) const;
    void draw(ModelComponent &model);
};

#endif // MODELRENDERSYSTEM_H
