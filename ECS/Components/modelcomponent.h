#ifndef MODELCOMPONENT_H
#define MODELCOMPONENT_H

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

#endif // MODELCOMPONENT_H
