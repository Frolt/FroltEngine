#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>


/**
   @brief The Texture struct stores an openGL texture ID,
    aswell as the texture type(diffuse, specular etc) and a path to the image file
 */
struct Texture
{
    Texture() = default;
    Texture(const std::string& path);

    unsigned int mTextureID;
    std::string mType;
    std::string mPath;
};

#endif // TEXTURE_H
