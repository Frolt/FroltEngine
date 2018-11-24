#include "materialfactory.h"
#include "path.h"
#include <QDebug>

MaterialFactory::MaterialFactory()
{
    loadTextures();
    loadCubemaps();
}

Texture MaterialFactory::getDiffuseTexture(const std::string &key)
{
    auto search = mTextures.find(key);
    if (search == mTextures.end()) {
        qDebug() << "ERROR:: \"" << key.c_str() << "\"" << "is not a valid key";
        return Texture();
    } else {
        search->second.mType = "diffuseMap";
        return search->second;
    }
}

Texture MaterialFactory::getSpecularTexture(const std::string &key)
{
    auto search = mTextures.find(key);
    if (search == mTextures.end()) {
        qDebug() << "ERROR:: \"" << key.c_str() << "\"" << "is not a valid key";
        return Texture();
    } else {
        search->second.mType = "specularMap";
        return search->second;
    }
}

Texture MaterialFactory::getEmissionTexture(const std::string &key)
{
    auto search = mTextures.find(key);
    if (search == mTextures.end()) {
        qDebug() << "ERROR:: \"" << key.c_str() << "\"" << "is not a valid key";
        return Texture();
    } else {
        search->second.mType = "emissionMap";
        return search->second;
    }
}

Cubemap MaterialFactory::getCubemap(const std::string &key)
{
    auto search = mCubemaps.find(key);
    qDebug() << search->second.mTextureID;
    if (search == mCubemaps.end()) {
        qDebug() << "ERROR:: \"" << key.c_str() << "\"" << "is not a valid key";
        return Cubemap();
    } else {
        return search->second;
    }
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
    mTextures["desert"] = Texture(Path::textures + "dessert1.jpg");
    mTextures["soilCrack"] = Texture(Path::textures + "soilCrack.jpg");
    mTextures["innSpec"] = Texture(Path::textures + "innLogoSpec.jpg");
}

void MaterialFactory::loadCubemaps()
{
    // Needs to load the 6 cubemaps in right, left, up, down, back, front order
    // Some of the cubemaps needs to be flipped (use bool argument in Cubemap constructor)

    // Lake
    std::vector<std::string> texturePaths = {
        "Lake/right.jpg",
        "Lake/left.jpg",
        "Lake/top.jpg",
        "Lake/bottom.jpg",
        "Lake/front.jpg",
        "Lake/back.jpg"
    };
    mCubemaps["lake"] = Cubemap(texturePaths);

    // Forest
    texturePaths = {
        "Forest/forest_rt.jpg",
        "Forest/forest_lf.jpg",
        "Forest/forest_up.jpg",
        "Forest/forest_dn.jpg",
        "Forest/forest_ft.jpg",
        "Forest/forest_bk.jpg"
    };
    mCubemaps["forest"] = Cubemap(texturePaths);

    // Mountain
    texturePaths = {
        "Mountain/mountain_rt.jpg",
        "Mountain/mountain_lf.jpg",
        "Mountain/mountain_up.jpg",
        "Mountain/mountain_dn.jpg",
        "Mountain/mountain_ft.jpg",
        "Mountain/mountain_bk.jpg"
    };
    mCubemaps["mountain"] = Cubemap(texturePaths);

    // BlueCloud
    texturePaths = {
        "BlueCloud/bluecloud_rt.jpg",
        "BlueCloud/bluecloud_lf.jpg",
        "BlueCloud/bluecloud_up.jpg",
        "BlueCloud/bluecloud_dn.jpg",
        "BlueCloud/bluecloud_ft.jpg",
        "BlueCloud/bluecloud_bk.jpg",
    };
    mCubemaps["blueCloud"] = Cubemap(texturePaths);

    // GrayCloud
    texturePaths = {
        "GrayCloud/graycloud_lf.jpg",
        "GrayCloud/graycloud_rt.jpg",
        "GrayCloud/graycloud_up.jpg",
        "GrayCloud/graycloud_dn.jpg",
        "GrayCloud/graycloud_ft.jpg",
        "GrayCloud/graycloud_bk.jpg",
    };
    mCubemaps["grayCloud"] = Cubemap(texturePaths);

    // Totality
    texturePaths = {
        "Totality/totality_rt.tga",
        "Totality/totality_lf.tga",
        "Totality/totality_up.tga",
        "Totality/totality_dn.tga",
        "Totality/totality_bk.tga",
        "Totality/totality_ft.tga",
    };
    mCubemaps["totality"] = Cubemap(texturePaths, true);
}
