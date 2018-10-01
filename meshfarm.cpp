#include "meshfarm.h"
#include "vertex.h"
#include <fstream>
#include "paths.h"
#include "ECS/Components/mesh_component.h"

MeshFarm::MeshFarm()
{
    initializeOpenGLFunctions();
    // Create all primitives
    createCube();
    createRectangle();

    // TODO only creates meshes when one is needed=?? example: createCube() function only;
}

MeshComponent MeshFarm::getCube(Shader *shader)
{
    return MeshComponent(shader, mVAO[CUBE], mDrawCount[CUBE], mUseIndices[CUBE]);
}

MeshComponent MeshFarm::getRectangle(Shader *shader)
{
    return MeshComponent(shader, mVAO[RECTANGLE], mDrawCount[RECTANGLE], mUseIndices[RECTANGLE]);
}

void MeshFarm::createCube()
{
    std::vector<Vertex> vertices = readVerticesFromFile("cube.dat");
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
}

void MeshFarm::createRectangle()
{
    std::vector<Vertex> vertices = readVerticesFromFile("rectangle.dat");
    std::vector<unsigned int> indices;
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
