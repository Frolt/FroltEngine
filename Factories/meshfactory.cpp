#include "meshfactory.h"
#include <fstream>
#include "ECS/Components/mesh_component.h"
#include "ECS/Components/model_component.h"
#include "vertex.h"
#include "path.h"
#include "octahedron.h"
#include "modelloader.h"


MeshFactory::MeshFactory(Shader *defaultShader)
    : mDefaultShader{defaultShader}
{
    initializeOpenGLFunctions();
}

MeshComponent MeshFactory::createCube(Shader *shader)
{
    QString name = "cube";
    if (!shader)
        shader = mDefaultShader;
    if (mMeshMap.find(name) == mMeshMap.end()) {
        qDebug() << " created cube (" << name << ")";
        std::vector<Vertex> vertices = readVerticesFromFile(name + ".dat");
        mMeshMap[name] = createWithoutIndices(vertices);
    }
    auto index = mMeshMap[name];
    return MeshComponent(*shader, mVAO[index], mDrawCount[index], mUseIndices[index]);
}

MeshComponent MeshFactory::createRectangle(Shader *shader)
{
    QString name = "rectangle";
    if (!shader)
        shader = mDefaultShader;
    if (mMeshMap.find(name) == mMeshMap.end()) {
        qDebug() << " created rectangle (" << name << ")";
        std::vector<Vertex> vertices = readVerticesFromFile(name + ".dat");
        std::vector<unsigned int> indices = { 0, 3, 1, 1, 3, 2 };
        mMeshMap[name] = createWithIndices(vertices, indices);
    }
    auto index = mMeshMap[name];
    return MeshComponent(*shader, mVAO[index], mDrawCount[index], mUseIndices[index]);
}

MeshComponent MeshFactory::createTriangle(Shader *shader)
{
    QString name = "triangle";
    if (!shader)
        shader = mDefaultShader;
    if (mMeshMap.find(name) == mMeshMap.end()) {
        qDebug() << " created triangle (" << name << ")";
        std::vector<Vertex> vertices = readVerticesFromFile(name + ".dat");
        mMeshMap[name] = createWithoutIndices(vertices);
    }
    auto index = mMeshMap[name];
    return MeshComponent(*shader, mVAO[index], mDrawCount[index], mUseIndices[index]);
}

MeshComponent MeshFactory::createSphere(unsigned int subDivide, Shader *shader)
{
    QString name = "sphere" + QString::number(subDivide);
    if (!shader)
        shader = mDefaultShader;
    if (mMeshMap.find(name) == mMeshMap.end()) {
        qDebug() << " created sphere (" << name << ")";
        // CREATE OCTAHEDRON
        // -------------------------------------------------------
        Octahedron sphere{subDivide};
        std::vector<Vertex> vertices = sphere.getVertices();
        mMeshMap[name] = createWithoutIndices(vertices);

        // -------------------------------------------------------
    }
    auto index = mMeshMap[name];
    return MeshComponent(*shader, mVAO[index], mDrawCount[index], mUseIndices[index]);
}

MeshComponent MeshFactory::createTerrain(const std::string &name, std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, Shader *shader)
{
    QString Name = name.c_str();
    if (!shader)
        shader = mDefaultShader;
    if (mMeshMap.find(Name) == mMeshMap.end()) {
        qDebug() << " created terrain (" << Name << ")";
        mMeshMap[Name] = createWithIndices(vertices, indices);
    }
    auto index = mMeshMap[Name];
    return MeshComponent(*shader, mVAO[index], mDrawCount[index], mUseIndices[index]);
}

ModelComponent MeshFactory::createModel(const std::string &path, Shader *shader)
{
    QString key = path.c_str();
    if (!shader)
        shader = mDefaultShader;
    if (mModels.find(key) == mModels.end()) {
        ModelLoader loader{path};
        ModelComponent model{*mDefaultShader};
        model.mMeshes = loader.mMeshes;
        mModels[key] = model;
    }
    return mModels[key];
}

MeshComponent MeshFactory::createTestTriangle(Shader *shader)
{
    QString name = "testTriangle";
    if (!shader)
        shader = mDefaultShader;
    if (mMeshMap.find(name) == mMeshMap.end()) {
        qDebug() << " created testTriangle (" << name << ")";
        std::vector<Vertex> vertices = readVerticesFromFile(name + ".dat");
        std::vector<unsigned int> indices = { 0, 1, 2, 1, 3, 2 };
        mMeshMap[name] = createWithIndices(vertices, indices);
    }
    auto index = mMeshMap[name];
    return MeshComponent(*shader, mVAO[index], mDrawCount[index], mUseIndices[index]);
}

unsigned int MeshFactory::createWithIndices(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices)
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

unsigned int MeshFactory::createWithoutIndices(std::vector<Vertex> &vertices)
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

std::vector<Vertex> MeshFactory::readVerticesFromFile(const QString &path)
{
    std::ifstream inf{Path::primitives + path.toStdString()};
    Q_ASSERT_X(inf, "SceneObject::readVerticesFromFile", "COULD_NOT_OPEN_FILE IN: \"FroltEngine/Assets/Primitives\"");

    std::vector<Vertex> vertices;
    am::Vec3 pos;
    am::Vec3 normal;
    am::Vec2 uv;
    char skip;
    std::string skipFirstLine;
    std::getline(inf, skipFirstLine);
    while (inf) {
        inf >> skip >> pos.x >> skip >> pos.y >> skip >> pos.z >> skip;
        inf >> skip >> normal.x >> skip >> normal.y >> skip >> normal.z >> skip;
        inf >> skip >> uv.x >> skip >> uv.y >> skip;
        if (!inf.eof())
            vertices.push_back(Vertex{pos, normal, uv});
    }
    return vertices;
}
