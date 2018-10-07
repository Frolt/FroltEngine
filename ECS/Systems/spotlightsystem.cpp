#include "spotlightsystem.h"
#include "ECS/Components/spotlight_component.h"
#include "ECS/Components/transform_component.h"
#include "ECS/Handles/componenthandle.h"

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
    ComponentHandle<SpotlightComponent> spotlight;
    ComponentHandle<TransformComponent> transform;
    for (auto entity : mRegisteredEntities) {
        mWorld->unpack(entity, spotlight, transform);
        setUniforms(spotlight(), transform());
    }
}

void SpotlightSystem::setUniforms(const SpotlightComponent &spotlight, const TransformComponent &transform) const
{
//    spotlight.mShader.use();
    spotlight.mShader.setVec3("spotLight.direction", spotlight.mDir);
    spotlight.mShader.setVec3("spotLight.position", transform.mPosition);
    spotlight.mShader.setVec3("spotLight.ambient", spotlight.mAmb);
    spotlight.mShader.setVec3("spotLight.diffuse", spotlight.mDiff);
    spotlight.mShader.setVec3("spotLight.specular", spotlight.mSpec);
    spotlight.mShader.setFloat("spotLight.innerCone", cos(am::toRadians(spotlight.mInnerCone)));
    spotlight.mShader.setFloat("spotLight.outerCone", cos(am::toRadians(spotlight.mOuterCone)));
    spotlight.mShader.setFloat("spotLight.constant", spotlight.mConstant);
    spotlight.mShader.setFloat("spotLight.linear", spotlight.mLinear);
    spotlight.mShader.setFloat("spotLight.quadratic", spotlight.mQuadratic);
}
