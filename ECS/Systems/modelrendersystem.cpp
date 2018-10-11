#include "modelrendersystem.h"

modelRenderSystem::modelRenderSystem()
{
    mSystemMask.addComponent<ModelComponent>();
    mSystemMask.addComponent<TransformComponent>();
    mSystemMask.addComponent<MaterialComponent>();
}

void modelRenderSystem::beginPlay()
{

}

void modelRenderSystem::update(float)
{
    for (auto entity : mRegisteredEntities) {
        ComponentHandle<ModelComponent> model;
        ComponentHandle<TransformComponent> transform;
        ComponentHandle<MaterialComponent> material;
        mWorld->unpack(entity, model, transform, material);
//        model().mShader.use();
        updateMaterialUniforms(model().mShader, material);
        updateTransformUniforms(model().mShader, transform);
        draw(model);
    }
}

void modelRenderSystem::updateMaterialUniforms(Shader shader, MaterialComponent &material)
{
    // Set rest of uniforms
    shader.setBool("material.isLight", material.mIsLight);
    shader.setBool("material.hasDiffMap", material.mHasDiffMap);
    shader.setBool("material.hasSpecMap", material.mHasSpecMap);
    shader.setBool("material.hasEmissionMap", material.mHasEmissionMap);
    shader.setVec3("material.diffuseColor", material.mDiffuseColor);
    shader.setVec3("material.specularColor", material.mSpecularColor);
    shader.setFloat("material.shininess", material.mShininess);
}

void modelRenderSystem::updateTransformUniforms(Shader shader, const TransformComponent &transform) const
{
    // Matrix transformation happens in reverse order
    //---------------------------------------------------------------------------------
    am::Mat4 modelMatrix;
    modelMatrix.translate(transform.mPosition);
    modelMatrix.rotate(transform.mEulerAngles.yaw(), am::up());
    modelMatrix.rotate(transform.mEulerAngles.pitch(), am::right());
    modelMatrix.rotate(transform.mEulerAngles.roll(), am::forward());
    modelMatrix.scale(transform.mScale);
    //---------------------------------------------------------------------------------

    // Create Normal Matrix
    auto m = modelMatrix;
    m.inverse();
    m.transpose();
    am::Mat3 normalMatrix = {
            m(0,0), m(0,1), m(0,2),
            m(1,0), m(1,1), m(1,2),
            m(2,0), m(2,1), m(2,2),
    };

    // Update shader uniforms
    shader.setMat4("model", modelMatrix);
    shader.setMat3("normalMat", normalMatrix);
}

void modelRenderSystem::draw(ModelComponent &model)
{
    for (auto &mesh : model.mMeshes) {
        mesh.draw(model.mShader);
    }
}
