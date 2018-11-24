#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <vector>
#include <string>

/**
   @brief The Cubemap struct loads 6 textures and maps them on a cube. It stores an openGL cubemap ID.
 */
struct Cubemap
{
    Cubemap() = default;
    Cubemap(std::vector<std::string> &mCubemapTextures, bool flipVertical = false);

    unsigned int mTextureID;
};

#endif // CUBEMAP_H
