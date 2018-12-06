#include "rendersystem.h"
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
    ch::Mesh mesh;
    ch::Transform transform;
    ch::Material material;
    for (auto &entity : mRegisteredEntities) {
        mWorld->unpack(entity, mesh, transform, material);
        updateMaterialUniforms(mesh().mShader, material);
        updateTransformUniforms(mesh().mShader, mWorld->getEntity(entity));
        draw(mesh);
    }
}

void RenderSystem::updateMaterialUniforms(const Shader shader, MaterialComponent &material)
{
    // Set uniform samplers(textures)
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int emissionNr = 1;
    for (unsigned int i = 0; i < material.mTextures.size(); i++) {
        glActiveTexture(GL_TEXTURE + i);
        std::string number;
        std::string name = material.mTextures[i].mType;
        if (name == "diffuseMap") {
            number = std::to_string(diffuseNr++);
            material.mHasDiffMap = true;
        } else if (name == "specularMap") {
            number = std::to_string(specularNr++);
            material.mHasSpecMap = true;
        } else if (name == "emissionMap") {
            number = std::to_string(emissionNr++);
            material.mHasEmissionMap = true;
        }
        shader.setInt("material." + name + number, i);
        glBindTexture(GL_TEXTURE_2D, material.mTextures[i].mTextureID);
    }
    glActiveTexture(GL_TEXTURE0);

    // Set rest of uniforms
    shader.setBool("material.isLight", material.mIsLight);
    shader.setBool("material.hasDiffMap", material.mHasDiffMap);
    shader.setBool("material.hasSpecMap", material.mHasSpecMap);
    shader.setBool("material.hasEmissionMap", material.mHasEmissionMap);
    shader.setVec3("material.diffuseColor", material.mDiffuseColor);
    shader.setVec3("material.specularColor", material.mSpecularColor);
    shader.setFloat("material.shininess", material.mShininess);
}

void RenderSystem::updateTransformUniforms(const Shader shader, EntityHandle entity)
{
    am::Mat4 modelMatrix = entity.getModelMatrix();

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

void RenderSystem::draw(const MeshComponent &mesh)
{
    glBindVertexArray(mesh.mVAO);

    if (mesh.mUseIndices)
        glDrawElements(GL_TRIANGLES, mesh.mDrawCount, GL_UNSIGNED_INT, nullptr);
    else
        glDrawArrays(GL_TRIANGLES, 0, mesh.mDrawCount);
}
