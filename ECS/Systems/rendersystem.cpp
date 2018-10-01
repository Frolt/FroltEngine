#include "rendersystem.h"
#include "ECS/Components/mesh_component.h"
#include "ECS/Components/transform_component.h"
#include "ECS/Components/material_component.h"
#include "ECS/Handles/componenthandle.h"
#include "world.h"
#include "shader.h"

RenderSystem::RenderSystem()
{
    initializeOpenGLFunctions();
    mSystemMask.addComponent<MeshComponent>();
    mSystemMask.addComponent<TransformComponent>();
    mSystemMask.addComponent<MaterialComponent>();
}

void RenderSystem::beginPlay()
{

}

void RenderSystem::update(float)
{
    for (auto entity : mRegisteredEntities) {
        qDebug() << "RenderSystem update()";
        ComponentHandle<MeshComponent> mesh;
        ComponentHandle<TransformComponent> transform;
        ComponentHandle<MaterialComponent> material;
        mWorld->unpack(entity, mesh, transform, material);

        mesh().mShader->use();
        updateShader(mesh().mShader, material());
        updateModelMatrix(mesh().mShader, transform());
        draw(mesh);
    }
}

void RenderSystem::draw(ComponentHandle<MeshComponent> &mesh)
{
    glBindVertexArray(mesh().mVAO);

    if (mesh().mUseIndices)
        glDrawElements(GL_TRIANGLES, mesh().mDrawCount, GL_UNSIGNED_INT, nullptr);
    else
        glDrawArrays(GL_TRIANGLES, 0, mesh().mDrawCount);
}

void RenderSystem::updateShader(Shader *shader, MaterialComponent &material)
{
    shader->setBool("material.hasDiffMap", material.mHasDiffMap);
    shader->setBool("material.hasSpecMap", material.mHasSpecMap);
    shader->setBool("material.hasEmissionMap", material.mHasEmissionMap);
    shader->setVec3("material.diffuseColor", material.mDiffuseColor);
    shader->setVec3("material.specularColor", material.mSpecularColor);
    shader->setFloat("material.shininess", material.mShininess);

    // TODO add textures
//    if (material.mHasDiffMap) {
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, material.mDiffuseMap->mID);
//    }
//    if (material.mHasSpecMap) {
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, material.mSpecularMap->mID);
//    }
//    if (material.mHasEmissionMap) {
//        glActiveTexture(GL_TEXTURE2);
//        glBindTexture(GL_TEXTURE_2D, material.mEmissionMap->mID);
//    }
}

void RenderSystem::updateModelMatrix(Shader *shader, TransformComponent &transform)
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

//    // TODO works?
//    shader->setMat4("model", modelMatrix);
//    shader->setMat3("normalMat", normalMatrix);
    // Update shader uniforms
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "model"), 1, GL_TRUE, modelMatrix.data());
    glUniformMatrix3fv(glGetUniformLocation(shader->ID, "normalMat"), 1, GL_TRUE, normalMatrix.data());
}
