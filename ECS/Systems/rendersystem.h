#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "ECS/system.h"
#include <QOpenGLFunctions_4_1_Core>

// Forward declarations
class Shader;
struct MaterialComponent;
struct TransformComponent;
struct MeshComponent;
template<typename T>
class ComponentHandle;

class RenderSystem : public System, protected QOpenGLFunctions_4_1_Core
{
public:
    RenderSystem();
    void beginPlay() override;
    void update(float) override;

    void draw(ComponentHandle<MeshComponent> &mesh);
    void updateMaterial(Shader *shader, MaterialComponent &material);
    void updateTransform(Shader *shader, TransformComponent &transform);
};

#endif // RENDERSYSTEM_H
