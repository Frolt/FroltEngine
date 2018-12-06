#include "skybox_component.h"


SkyboxComponent::SkyboxComponent(const Shader &skyboxShader, const Shader &defaultShader)
    : mSkyboxShader{skyboxShader}, mDefaultShader{defaultShader}
{

}
