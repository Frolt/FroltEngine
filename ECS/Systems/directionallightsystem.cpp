#include "directionallightsystem.h"
#include "shader.h"


DirectionalLightSystem::DirectionalLightSystem()
{
    mSystemMask.addComponent<DirectionalLightComponent>();
}

void DirectionalLightSystem::beginPlay()
{

}

void DirectionalLightSystem::update(float)
{
    ch::DirLight dirLight;
    for (auto &entity : mRegisteredEntities) {
        mWorld->unpack(entity, dirLight);
        updateUniforms(dirLight);
    }
}

void DirectionalLightSystem::updateUniforms(const DirectionalLightComponent &dirLight) const
{
//    dirLight.mShader.use();
    dirLight.mShader.setVec3("dirLight.direction", dirLight.mDir);
    dirLight.mShader.setVec3("dirLight.ambient", dirLight.mAmb);
    dirLight.mShader.setVec3("dirLight.diffuse", dirLight.mDiff);
}
