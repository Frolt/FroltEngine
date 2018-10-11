#ifndef MATERIALFACTORY_H
#define MATERIALFACTORY_H

#include <unordered_map>
#include <map>
#include "texture.h"

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
