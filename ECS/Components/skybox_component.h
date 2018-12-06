#ifndef SKYBOX_COMPONENT_H
#define SKYBOX_COMPONENT_H

#include "ECS/component.h"
#include "cubemap.h"
#include "shader.h"


struct SkyboxComponent : public Component<SkyboxComponent>
{
    SkyboxComponent() = default;
    SkyboxComponent(const Shader &skyboxShader, const Shader &defaultShader);

    Cubemap mCubemap;
    Shader mSkyboxShader;
    Shader mDefaultShader;
};

#endif // SKYBOX_COMPONENT_H
