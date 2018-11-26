#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    : mVertices{vertices},
      mIndices{indices},
      mTextures{textures}
{
    gl->initializeOpenGLFunctions();
    setupMesh();
}

void Mesh::draw(Shader &shader)
{
    // Set uniform samplers in shader
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for (unsigned int i = 0; i < mTextures.size(); i++) {
        gl->glActiveTexture(GL_TEXTURE + i);
        std::string number;
        std::string name = mTextures[i].mType;
        if (name == "diffuseMap")
            number = std::to_string(diffuseNr++);
        if (name == "specularMap")
            number = std::to_string(specularNr++);
        shader.setInt("material." + name, i);
        gl->glBindTexture(GL_TEXTURE_2D, mTextures[i].mTextureID);
    }
    gl->glActiveTexture(GL_TEXTURE0);

    // Draw mesh
    gl->glBindVertexArray(mVAO);
    gl->glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mIndices.size()), GL_UNSIGNED_INT, nullptr);
    gl->glBindVertexArray(0);
}

void Mesh::setupMesh()
{
    unsigned int VBO, EBO;
    gl->glGenVertexArrays(1, &mVAO);
    gl->glGenBuffers(1, &VBO);
    gl->glGenBuffers(1, &EBO);

    gl->glBindVertexArray(mVAO);
    gl->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    gl->glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);
    gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    gl->glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), mIndices.data(), GL_STATIC_DRAW);

    gl->glEnableVertexAttribArray(0);
    gl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mPosition));
    gl->glEnableVertexAttribArray(1);
    gl->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mNormal));
    gl->glEnableVertexAttribArray(2);
    gl->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mUV));

    gl->glBindVertexArray(0);
}
