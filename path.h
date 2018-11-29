#ifndef PATH_H
#define PATH_H

#include <string>

/// Contains relative paths to subdirectories inside the project directory
namespace Path
{
    const std::string root = "../FroltEngine/";
    const std::string assets = "../FroltEngine/Assets/";
    const std::string textures = "../FroltEngine/Assets/Textures/";
    const std::string skyboxes = "../FroltEngine/Assets/Skyboxes/";
    const std::string primitives = "../FroltEngine/Assets/Primitives/";
    const std::string models = "../FroltEngine/Assets/Models/";
    const std::string shaders = "../FroltEngine/Shaders/";
    const std::string mapdata = "../FroltEngine/LAS/MapData/";
};


#endif // PATH_H
