#include "texture.h"
#include <iostream>
#include <QOpenGLFunctions_4_1_Core>
#include <QDebug>
#include "stb_image.h"
#include <memory>

Texture::Texture(const std::string& path)
{
    auto gl = std::make_unique<QOpenGLFunctions_4_1_Core>();
    gl->initializeOpenGLFunctions();
    // Texture settings
    gl->glGenTextures(1, &mID);
    gl->glBindTexture(GL_TEXTURE_2D, mID);
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load texture
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    // Load image to our texture object and create mipmaps
    if (data) {
        auto extension = path.substr(path.find_last_of(".") + 1);
        if (extension == "jpg") {
            gl->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            gl->glGenerateMipmap(GL_TEXTURE_2D);
        } else if (extension == "png") {
            gl->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            gl->glGenerateMipmap(GL_TEXTURE_2D);
        }
    } else {
        qDebug() << "Failed to load texture" << path.c_str();
    }
    // Free texture memory
    stbi_image_free(data);
}

