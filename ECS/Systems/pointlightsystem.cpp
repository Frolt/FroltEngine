#include "pointlightsystem.h"
#include "ECS/Components/pointlight_component.h"
#include "ECS/Components/transform_component.h"
#include "ECS/Handles/componenthandle.h"

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
    ComponentHandle<PointLightComponent> pointLight;
    ComponentHandle<TransformComponent> transform;
    for (auto entity : mRegisteredEntities) {
        mWorld->unpack(entity, pointLight, transform);
        setUniforms(pointLight(), transform());
    }
}

void PointLightSystem::setUniforms(const PointLightComponent &dirLight, const TransformComponent &transform) const
{
//    dirLight.mShader.use();
    dirLight.mShader.setVec3("pointLights[0].position", transform.mPosition);
    dirLight.mShader.setVec3("pointLights[0].ambient", dirLight.mAmb);
    dirLight.mShader.setVec3("pointLights[0].diffuse", dirLight.mDiff);
    dirLight.mShader.setVec3("pointLights[0].specular", dirLight.mSpec);
    dirLight.mShader.setFloat("pointLights[0].constant", dirLight.mConstant);
    dirLight.mShader.setFloat("pointLights[0].linear", dirLight.mLinear);
    dirLight.mShader.setFloat("pointLights[0].quadratic", dirLight.mQuadratic);
}
