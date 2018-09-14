#ifndef GL_CONSTANTS_H
#define GL_CONSTANTS_H

#include <string>

static std::string dir = "../";
static std::string texDir = "../Textures/";
static std::string shaderDir = "../Shaders/";
static std::string verticesDir = "../VerticesData/";
static std::string mapDir = "../MapData/";
static std::string ModelDir = "../Models/";

enum SHADERS {
    TEXTURE,
    COLOR,
    LIGHT,
    LIGHT_SOURCE
};

#endif // GL_CONSTANTS_H
