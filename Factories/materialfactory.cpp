#include "materialfactory.h"
#include "paths.h"
#include <QDebug>

MaterialFactory::MaterialFactory()
{
    loadTextures();
}

Texture MaterialFactory::getDiffuseTexture(const std::string &key)
{
    if (mTextures.find(key) == mTextures.end()) {
        qDebug() << "ERROR:: \"" << key.c_str() << "\"" << "is not a valid key";
    }
    auto texture = mTextures[key];
    texture.mType = "diffuseMap";
    return texture;
}

Texture MaterialFactory::getSpecularTexture(const std::string &key)
{
    if (mTextures.find(key) == mTextures.end()) {
        qDebug() << "ERROR:: \"" << key.c_str() << "\"" << "is not a valid key";
    }
    auto texture = mTextures[key];
    texture.mType = "specularMap";
    return texture;
}

Texture MaterialFactory::getEmissionTexture(const std::string &key)
{
    if (mTextures.find(key) == mTextures.end()) {
        qDebug() << "ERROR:: \"" << key.c_str() << "\"" << "is not a valid key";
    }
    auto texture = mTextures[key];
    texture.mType = "emissionMap";
    return texture;
}

void MaterialFactory::loadTextures()
{
    mTextures["container"] = Texture(Path::textures + "container.png");
    mTextures["containerSpecular"] = Texture(Path::textures + "container_specular.png");
    mTextures["wall"] = Texture(Path::textures + "wall.jpg");
    mTextures["inn"] = Texture(Path::textures + "innLogo.jpg");
    mTextures["awesomeface"] = Texture(Path::textures + "awesomeface.png");
    mTextures["wood"] = Texture(Path::textures + "wood.jpg");
    mTextures["matrix"] = Texture(Path::textures + "matrix.jpg");
    mTextures["kermit"] = Texture(Path::textures + "kermit.jpg");
    mTextures["palmBark"] = Texture(Path::textures + "palm_bark.png");
    mTextures["palmLeaves"] = Texture(Path::textures + "palm leafs.png");
}
