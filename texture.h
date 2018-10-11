#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

struct Texture
{
    Texture() = default;
    Texture(const std::string& path);

    unsigned int mID;
    std::string mType;
    std::string mPath;
};

#endif // TEXTURE_H
