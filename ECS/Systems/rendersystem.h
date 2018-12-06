#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "ECS/system.h"
#include <QOpenGLFunctions_4_1_Core>


/**
   @brief The RenderSystem class renders all entities with a mesh component to the viewport
 */
class RenderSystem : public System, protected QOpenGLFunctions_4_1_Core
{
public:
    RenderSystem();
    void beginPlay() override;
    void update(float) override;

    void updateMaterialUniforms(const Shader shader, MaterialComponent &material);
    void updateTransformUniforms(const Shader shader, EntityHandle entity);
    void draw(const MeshComponent &mesh);
};

#endif // RENDERSYSTEM_H
