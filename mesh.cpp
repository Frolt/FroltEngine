#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<Texture> > textures)
    : mVertices{vertices},
      mIndices{indices},
      mTextures{textures}
{
    initializeOpenGLFunctions();
    setupMesh();
}

void Mesh::draw(Shader &shader)
{
    // Set uniform samplers in shader
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for (unsigned int i = 0; i < mTextures.size(); i++) {
        glActiveTexture(GL_TEXTURE + i);
        std::string number;
        std::string name = mTextures[i]->mType;
        if (name == "diffuseMap")
            number = std::to_string(diffuseNr++);
        if (name == "specularMap")
            number = std::to_string(specularNr++);
        shader.setInt("material." + name, i);
        glBindTexture(GL_TEXTURE_2D, mTextures[i]->mID);
    }
    glActiveTexture(GL_TEXTURE0);

    // Draw mesh
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Mesh::setupMesh()
{
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), mIndices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mPosition));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mNormal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mUV));

    glBindVertexArray(0);
}
