#include "meshfarm.h"
#include "vertex.h"
#include <fstream>
#include "paths.h"
#include "enums.h"
#include "ECS/Components/mesh_component.h"

MeshFarm::MeshFarm(Shader *defaultShader)
    : mDefaultShader{defaultShader}
{
    initializeOpenGLFunctions();
    // Create all primitives
    createCube();
    createRectangle();

    // TODO only creates meshes when one is needed=?? example: createCube() function only;
}

MeshComponent MeshFarm::createCube(Shader *shader)
{
    if (!shader)
        shader = mDefaultShader;
    if (mMeshMap.find("cube") == mMeshMap.end()) {
        qDebug() << "cube created";
        std::vector<Vertex> vertices = readVerticesFromFile("cube.dat");
        mMeshMap["cube"] = createWithoutIndices(vertices);
    }
    auto index = mMeshMap["cube"];
    return MeshComponent(shader, mVAO[index], mDrawCount[index], mUseIndices[index]);
}

MeshComponent MeshFarm::createRectangle(Shader *shader)
{
    if (!shader)
        shader = mDefaultShader;
    if (mMeshMap.find("rectangle") == mMeshMap.end()) {
        qDebug() << "rectangle created";
        std::vector<Vertex> vertices = readVerticesFromFile("rectangle.dat");
        std::vector<unsigned int> indices = { 0, 3, 1, 1, 3, 2 };
        mMeshMap["rectangle"] = createWithIndices(vertices, indices);
    }
    auto index = mMeshMap["rectangle"];
    return MeshComponent(shader, mVAO[index], mDrawCount[index], mUseIndices[index]);
}

unsigned int MeshFarm::createWithIndices(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices)
{
    unsigned int VAO, VBO, EBO;

    // Activate VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // Buffer vertices
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    // Buffer indices
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    // Vertex attribute settings
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mPosition));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mNormal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mUV));
    // Enable attributes
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // Store our VAO
    mVAO.push_back(VAO);
    mDrawCount.push_back(static_cast<unsigned int>(indices.size()));
    mUseIndices.push_back(true);
    return static_cast<unsigned int>(mVAO.size()-1);
}

unsigned int MeshFarm::createWithoutIndices(std::vector<Vertex> &vertices)
{
    unsigned int VAO, VBO;

    // Activate VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // Buffer vertices
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    // Vertex attribute settings
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mPosition));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mNormal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mUV));
    // Enable attributes
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // Store our VAO
    mVAO.push_back(VAO);
    mDrawCount.push_back(static_cast<unsigned int>(vertices.size()));
    mUseIndices.push_back(false);
    return static_cast<unsigned int>(mVAO.size()-1);
}

std::vector<Vertex> MeshFarm::readVerticesFromFile(const std::string &path)
{
    std::ifstream inf{primitivesDir + path};
    Q_ASSERT_X(inf, "SceneObject::readVerticesFromFile", "COULD_NOT_OPEN_FILE");

    std::vector<Vertex> vertices;
    am::Vec3 pos;
    am::Vec3 normal;
    am::Vec2 uv;
    char skip;
    while (inf) {
        inf >> skip >> pos.x >> skip >> pos.y >> skip >> pos.z >> skip;
        inf >> skip >> normal.x >> skip >> normal.y >> skip >> normal.z >> skip;
        inf >> skip >> uv.x >> skip >> uv.y >> skip;
        vertices.push_back(Vertex{pos, normal, uv});
    }
    vertices.pop_back();
    return vertices;
}
