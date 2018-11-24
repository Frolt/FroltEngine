#include "skyboxsystem.h"

SkyboxSystem::SkyboxSystem()
{
    initializeOpenGLFunctions();
    mSystemMask.addComponent<SkyboxComponent>();
    mSystemMask.addComponent<MeshComponent>();
    mSystemMask.addComponent<TransformComponent>();
}

void SkyboxSystem::beginPlay()
{

}

void SkyboxSystem::update(float deltaTime)
{
    ch::Skybox skybox;
    ch::Transform transform;
    ch::Mesh mesh;
    for (auto entity : mRegisteredEntities) {
        mWorld->unpack(entity, skybox, transform, mesh);
        updateCubemapUniform(skybox, mesh);
    }
}

void SkyboxSystem::updateCubemapUniform(const SkyboxComponent &skybox, const MeshComponent &mesh)
{
    // Activate default shader
    skybox.mSkyboxShader.use();
//    skybox.mSkyboxShader.setMat4("view", );
//    skybox.mSkyboxShader.setMat4("projection", );

    // Disable depthMask while drawing skybox
    glDepthMask(GL_FALSE);

    // Activate cubemap uniform and bind our skybox texture to it
    glActiveTexture(GL_TEXTURE_CUBE_MAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.mCubemap.mTextureID);

    // Draw mesh
    glBindVertexArray(mesh.mVAO);
    glDrawArrays(GL_TRIANGLES, 0, mesh.mDrawCount);

    // Enable depth mask after we are done
    glDepthMask(GL_TRUE);

    // Enable default shader
    skybox.mDefaultShader.use();
}
