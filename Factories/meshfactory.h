#ifndef MESHFACTORY_H
#define MESHFACTORY_H

#include <vector>
#include <QOpenGLFunctions_4_1_Core>
#include <QString>
#include <QHash>

// Forward declarations
struct Vertex;
struct MeshComponent;
struct ModelComponent;
class Shader;

/**
   @brief The MeshFactory class is used to make meshes.
    It will only create the mesh the first time it is used by an entity,
    after that it will reuse the meshes
 */
class MeshFactory : protected QOpenGLFunctions_4_1_Core
{
public:
    MeshFactory(Shader *defaultShader);
    MeshComponent createCube(Shader *shader = nullptr);
    MeshComponent createRectangle(Shader *shader = nullptr);
    MeshComponent createTriangle(Shader *shader = nullptr);
    MeshComponent createSphere(unsigned int subDivide = 3, Shader *shader = nullptr);
    MeshComponent createTerrain(const std::string &name, std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, Shader *shader = nullptr);
    ModelComponent createModel(const std::string &path, Shader *shader = nullptr);
    MeshComponent createTestTriangle(Shader *shader = nullptr);

private:
    unsigned int createWithIndices(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
    unsigned int createWithoutIndices(std::vector<Vertex> &vertices);
    std::vector<Vertex> readVerticesFromFile(const QString &path);

private:
    QHash<QString, unsigned int> mMeshMap;
    std::vector<unsigned int> mVAO;
    std::vector<unsigned int> mDrawCount;
    std::vector<bool> mUseIndices;

    QHash<QString, ModelComponent> mModels;


    Shader *mDefaultShader;
};

#endif // MESHFACTORY_H
