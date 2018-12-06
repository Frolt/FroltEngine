#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include "ECS/component.h"
#include "shader.h"


struct MeshComponent : public Component<MeshComponent>
{
    MeshComponent() = default;
    MeshComponent(Shader shader, unsigned int VAO, unsigned int drawCount, bool useIndices = false);

    Shader mShader;
    unsigned int mVAO{0};
    unsigned int mDrawCount{0};
    bool mUseIndices{false};
};

#endif // MESH_COMPONENT_H
