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
struct ComponentHandle;

class RenderSystem : public System, protected QOpenGLFunctions_4_1_Core
{
public:
    RenderSystem();
    void beginPlay() override;
    void update(float) override;

    void updateMaterial(Shader shader, const MaterialComponent &material) const;
    void updateTransform(Shader shader, const TransformComponent &transform) const;
    void draw(const ComponentHandle<MeshComponent> &mesh);
};

#endif // RENDERSYSTEM_H
