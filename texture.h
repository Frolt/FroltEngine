#ifndef TEXTURE_H
#define TEXTURE_H

#include <QOpenGLFunctions_4_1_Core>
#include <string>

class Texture : protected QOpenGLFunctions_4_1_Core
{
public:
    Texture(const std::string& path);

    unsigned int mID;
    std::string mType;
    std::string mPath;
};

#endif // TEXTURE_H
