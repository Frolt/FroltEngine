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
    mTextures["containerSpec"] = Texture(Path::textures + "container_specular.png");
    mTextures["wall"] = Texture(Path::textures + "wall.jpg");
    mTextures["inn"] = Texture(Path::textures + "innLogo.jpg");
    mTextures["awesomeface"] = Texture(Path::textures + "awesomeface.png");
    mTextures["wood"] = Texture(Path::textures + "wood.jpg");
    mTextures["matrix"] = Texture(Path::textures + "matrix.jpg");
    mTextures["kermit"] = Texture(Path::textures + "kermit.jpg");
    mTextures["snow1"] = Texture(Path::textures + "snow1.jpg");
    mTextures["snow2"] = Texture(Path::textures + "snow2.jpg");
    mTextures["grass"] = Texture(Path::textures + "grass1.jpg");
    mTextures["stoneTile"] = Texture(Path::textures + "stoneTile.jpg");
    mTextures["dessert"] = Texture(Path::textures + "dessert1.jpg");
    mTextures["soilCrack"] = Texture(Path::textures + "soilCrack.jpg");
    mTextures["innSpec"] = Texture(Path::textures + "innLogoSpec.jpg");
}
