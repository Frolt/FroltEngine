#ifndef MATERIALFACTORY_H
#define MATERIALFACTORY_H

#include <unordered_map>
#include <map>
#include "texture.h"

/**
   @brief The MaterialFactory class is used to get preloaded textures
    as a diffuse, specular or emission map for a material
 */
class MaterialFactory
{
public:
    MaterialFactory();
    Texture getDiffuseTexture(const std::string &key);
    Texture getSpecularTexture(const std::string &key);
    Texture getEmissionTexture(const std::string &key);

private:
    void loadTextures();

    std::unordered_map<std::string, Texture> mTextures;
};

#endif // MATERIALFACTORY_H
