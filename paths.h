#ifndef PATHS_H
#define PATHS_H

#include <string>

// TODO snakk med Ole, singleton?
// TODO snakk med Ole, namespace isteden?

struct Path
{
    static const std::string root;
    static const std::string textures;
    static const std::string shaders;
    static const std::string primitives;
    static const std::string mapdata;
    static const std::string models;

private:
    Path() = default;
};


#endif // PATHS_H
