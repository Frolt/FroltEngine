#ifndef MODEL_COMPONENT_H
#define MODEL_COMPONENT_H

#include <vector>
#include "ECS/component.h"
#include "mesh.h"
#include "shader.h"


struct ModelComponent : public Component<ModelComponent>
{
    ModelComponent() = default;
    ModelComponent(Shader shader);

    Shader mShader;
    std::vector<Mesh> mMeshes;
};

#endif // MODEL_COMPONENT_H
