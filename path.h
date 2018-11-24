#ifndef PATH_H
#define PATH_H

#include <string>

/// Contains relative paths to subdirectories inside the project directory
namespace Path
{
    const std::string root = "../";
    const std::string assets = "../Assets/";
    const std::string textures = "../Assets/Textures/";
    const std::string skyboxes = "../Assets/Skyboxes/";
    const std::string primitives = "../Assets/Primitives/";
    const std::string models = "../Assets/Models/";
    const std::string shaders = "../Shaders/";
    const std::string mapdata = "../LAS/MapData/";
};


#endif // PATH_H
