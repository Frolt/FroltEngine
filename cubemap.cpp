#include "cubemap.h"
#include <QOpenGLFunctions_4_1_Core>
#include <QDebug>
#include "stb_image.h"
#include "path.h"

Cubemap::Cubemap(std::vector<std::string> &mCubemapTextures, bool flipVertical)
{
    // Initialize opengl functions
    auto gl = std::make_unique<QOpenGLFunctions_4_1_Core>();
    gl->initializeOpenGLFunctions();

    // Generate cubemap
    gl->glGenTextures(1, &mTextureID);
    gl->glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureID);

    // Wrapping/filtering settings
    gl->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gl->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    gl->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    gl->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Set all 6 cubemap textures
    int width, height, nrChannels;
    unsigned char *data;
    stbi_set_flip_vertically_on_load(flipVertical);
    for(unsigned int i = 0; i < mCubemapTextures.size(); i++) {
        data = stbi_load((Path::skyboxes + mCubemapTextures[i]).c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            gl->glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            qDebug() << "Failed to load cubemap texture" << (Path::skyboxes + mCubemapTextures[i]).c_str();
            stbi_image_free(data);
        }
    }
}
