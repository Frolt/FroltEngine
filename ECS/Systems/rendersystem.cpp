#include "rendersystem.h"
#include "ECS/Components/mesh_component.h"
#include "ECS/Components/transform_component.h"
#include "ECS/Components/material_component.h"
#include "ECS/Handles/componenthandle.h"
#include "world.h"
#include "shader.h"
#include "texture.h"

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
        ComponentHandle<MeshComponent> mesh;
        ComponentHandle<TransformComponent> transform;
        ComponentHandle<MaterialComponent> material;
        mWorld->unpack(entity, mesh, transform, material);

//        mesh().mShader.use();
        updateMaterialUniforms(mesh().mShader, material());
        updateTransformUniforms(mesh().mShader, transform());
        draw(mesh);
    }
}

void RenderSystem::updateMaterialUniforms(Shader shader, const MaterialComponent &material) const
{
    shader.setBool("material.hasDiffMap", material.mHasDiffMap);
    shader.setBool("material.hasSpecMap", material.mHasSpecMap);
    shader.setBool("material.hasEmissionMap", material.mHasEmissionMap);
    shader.setVec3("material.diffuseColor", material.mDiffuseColor);
    shader.setVec3("material.specularColor", material.mSpecularColor);
    shader.setFloat("material.shininess", material.mShininess);

//    // Set uniform samplers in shader
//    unsigned int diffuseNr = 1;
//    unsigned int specularNr = 1;
//    for (unsigned int i = 0; i < material.mTextures.size(); i++) {
//        glActiveTexture(GL_TEXTURE + i);
//        std::string number;
//        std::string name = material.mTextures[i].mType;
//        if (name == "diffuseMap")
//            number = std::to_string(diffuseNr++);
//        if (name == "specularMap")
//            number = std::to_string(specularNr++);
//        shader.setInt("material." + name, i);
//        glBindTexture(GL_TEXTURE_2D, material.mTextures[i].mID);
//    }
//    // Unbind texture
//    glActiveTexture(GL_TEXTURE0);
}

void RenderSystem::updateTransformUniforms(Shader shader, const TransformComponent &transform) const
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

void RenderSystem::draw(const ComponentHandle<MeshComponent> &mesh)
{
    glBindVertexArray(mesh().mVAO);

    if (mesh().mUseIndices)
        glDrawElements(GL_TRIANGLES, mesh().mDrawCount, GL_UNSIGNED_INT, nullptr);
    else
        glDrawArrays(GL_TRIANGLES, 0, mesh().mDrawCount);
}
