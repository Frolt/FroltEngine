#include "modelrendersystem.h"

ModelRenderSystem::ModelRenderSystem()
{
    mSystemMask.addComponent<ModelComponent>();
    mSystemMask.addComponent<TransformComponent>();
    mSystemMask.addComponent<MaterialComponent>();
}

void ModelRenderSystem::beginPlay()
{

}

void ModelRenderSystem::update(float)
{
    ch::Model model;
    ch::Transform transform;
    ch::Material material;
    for (auto &entity : mRegisteredEntities) {
        mWorld->unpack(entity, model, transform, material);
//        model().mShader.use();
        updateMaterialUniforms(model().mShader, material);
        updateTransformUniforms(model().mShader, transform);
        draw(model);
    }
}

void ModelRenderSystem::updateMaterialUniforms(const Shader shader, const MaterialComponent &material) const
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

void ModelRenderSystem::updateTransformUniforms(const Shader shader, const TransformComponent &transform) const
{
    // Matrix transformation happens in reverse order
    //---------------------------------------------------------------------------------
    am::Mat4 modelMatrix;
    modelMatrix.translate(transform.mLocation);
    modelMatrix.rotate(transform.mRotation.yaw, am::up());
    modelMatrix.rotate(transform.mRotation.pitch, am::right());
    modelMatrix.rotate(transform.mRotation.roll, am::forward());
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

void ModelRenderSystem::draw(ModelComponent &model)
{
    for (auto &mesh : model.mMeshes) {
        mesh.draw(model.mShader);
    }
}
