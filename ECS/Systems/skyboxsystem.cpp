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

void SkyboxSystem::update(float)
{
    ch::Skybox skybox;
    ch::Transform transform;
    ch::Mesh mesh;
    for (auto entity : mRegisteredEntities) {
        mWorld->unpack(entity, skybox, transform, mesh);
        drawCubemap(skybox, mesh);
    }
}

void SkyboxSystem::drawCubemap(const SkyboxComponent &skybox, const MeshComponent &mesh)
{
    // Disable depthMask while drawing skybox
    glDepthMask(GL_FALSE);
    skybox.mSkyboxShader.use();
    glBindVertexArray(mesh.mVAO);

    // Bind cubemap and draw
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.mCubemap.mTextureID);
    glDrawArrays(GL_TRIANGLES, 0, mesh.mDrawCount);

    // Turn depth mask and default shader back on
    glDepthMask(GL_TRUE);
    skybox.mDefaultShader.use();
}
