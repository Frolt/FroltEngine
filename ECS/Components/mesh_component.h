#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include "ECS/component.h"

// Forward declarations
class Shader;

struct MeshComponent : public Component<MeshComponent>
{
    MeshComponent() {}
    MeshComponent(Shader* shader, unsigned int VAO, unsigned int drawCount, bool useIndices = false)
        : mShader{shader}, mVAO{VAO}, mDrawCount{drawCount}, mUseIndices{useIndices} {}

    Shader *mShader{nullptr};
    unsigned int mVAO{0};
    unsigned int mDrawCount{0};
    bool mUseIndices{false};
};

#endif // MESH_COMPONENT_H
