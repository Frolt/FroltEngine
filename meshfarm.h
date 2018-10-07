#ifndef MESHFARM_H
#define MESHFARM_H

#include <vector>
#include <QOpenGLFunctions_4_1_Core>
#include <QString>
#include <QHash>

// Forward declarations
struct Vertex;
struct MeshComponent;
class Shader;

class MeshFarm : protected QOpenGLFunctions_4_1_Core
{
public:
    MeshFarm(Shader *defaultShader);
    MeshComponent createCube(Shader *shader = nullptr);
    MeshComponent createRectangle(Shader *shader = nullptr);
    MeshComponent createTriangle(Shader *shader = nullptr);
    MeshComponent createSphere(unsigned int subDivide = 3, Shader *shader = nullptr);

private:
    unsigned int createWithIndices(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
    unsigned int createWithoutIndices(std::vector<Vertex> &vertices);
    std::vector<Vertex> readVerticesFromFile(const QString &path);

private:
    QHash<QString, unsigned int> mMeshMap;
    std::vector<unsigned int> mVAO;
    std::vector<unsigned int> mDrawCount;
    std::vector<bool> mUseIndices;
    Shader *mDefaultShader;
};

#endif // MESHFARM_H
