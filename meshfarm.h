#ifndef MESHFARM_H
#define MESHFARM_H

#include <vector>
#include <tuple>
#include <QOpenGLFunctions_4_1_Core>
#include "enums.h"

// Forward declarations
struct Vertex;
struct MeshComponent;
class Shader;

class MeshFarm : protected QOpenGLFunctions_4_1_Core
{
public:
    MeshFarm();
    MeshComponent getCube(Shader *shader);
    MeshComponent getRectangle(Shader *shader);
private:
    void createCube();
    void createRectangle();
    std::vector<Vertex> readVerticesFromFile(const std::string &path);

private:
    std::vector<unsigned int> mVAO;
    std::vector<unsigned int> mDrawCount;
    std::vector<bool> mUseIndices;
    std::vector<Shader*> mShaders;
};

#endif // MESHFARM_H
