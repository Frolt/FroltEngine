#include "pointlightsystem.h"


PointLightSystem::PointLightSystem()
{
    mSystemMask.addComponent<PointLightComponent>();
    mSystemMask.addComponent<TransformComponent>();
}

void PointLightSystem::beginPlay()
{

}

void PointLightSystem::update(float)
{
    ch::PointLight pointLight;
    ch::Transform transform;
    for (auto &entity : mRegisteredEntities) {
        mWorld->unpack(entity, pointLight, transform);
        updateUniforms(pointLight, transform);
    }
}

void PointLightSystem::updateUniforms(const PointLightComponent &dirLight, const TransformComponent &transform) const
{
//    dirLight.mShader.use();
    dirLight.mShader.setVec3("pointLights[" + std::to_string(dirLight.mLightInstance) + "].position", transform.mLocation);
    dirLight.mShader.setVec3("pointLights[" + std::to_string(dirLight.mLightInstance) + "].diffuse", dirLight.mDiff);
    dirLight.mShader.setFloat("pointLights[" + std::to_string(dirLight.mLightInstance) + "].constant", dirLight.mConstant);
    dirLight.mShader.setFloat("pointLights[" + std::to_string(dirLight.mLightInstance) + "].linear", dirLight.mLinear);
    dirLight.mShader.setFloat("pointLights[" + std::to_string(dirLight.mLightInstance) + "].quadratic", dirLight.mQuadratic);
}
