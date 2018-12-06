#include "spotlightsystem.h"


SpotlightSystem::SpotlightSystem()
{
    mSystemMask.addComponent<SpotlightComponent>();
    mSystemMask.addComponent<TransformComponent>();
}

void SpotlightSystem::beginPlay()
{

}

void SpotlightSystem::update(float)
{
    ch::Spotlight spotlight;
    ch::Transform transform;
    for (auto &entity : mRegisteredEntities) {
        mWorld->unpack(entity, spotlight, transform);
        updateUniforms(spotlight, transform);
    }
}

void SpotlightSystem::updateUniforms(const SpotlightComponent &spotlight, const TransformComponent &transform) const
{
//    spotlight.mShader.use();
    spotlight.mShader.setVec3("spotLights[" + std::to_string(spotlight.mLightInstance) + "].direction", spotlight.mDir);
    spotlight.mShader.setVec3("spotLights[" + std::to_string(spotlight.mLightInstance) + "].position", transform.mLocation);
    spotlight.mShader.setVec3("spotLights[" + std::to_string(spotlight.mLightInstance) + "].diffuse", spotlight.mDiff);
    spotlight.mShader.setFloat("spotLights[" + std::to_string(spotlight.mLightInstance) + "].innerCone", cos(am::toRadians(spotlight.mInnerCone)));
    spotlight.mShader.setFloat("spotLights[" + std::to_string(spotlight.mLightInstance) + "].outerCone", cos(am::toRadians(spotlight.mOuterCone)));
    spotlight.mShader.setFloat("spotLights[" + std::to_string(spotlight.mLightInstance) + "].constant", spotlight.mConstant);
    spotlight.mShader.setFloat("spotLights[" + std::to_string(spotlight.mLightInstance) + "].linear", spotlight.mLinear);
    spotlight.mShader.setFloat("spotLights[" + std::to_string(spotlight.mLightInstance) + "].quadratic", spotlight.mQuadratic);
}
