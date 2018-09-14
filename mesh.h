#ifndef MESH_H
#define MESH_H

#include <QOpenGLFunctions_4_1_Core>
#include <vector>
#include <memory>
#include "vertex.h"
#include "texture.h"
#include "shader.h"

class Mesh : protected QOpenGLFunctions_4_1_Core
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<Texture>> textures);
    void draw(Shader &shader);
private:
    void setupMesh();

private:
    unsigned int mVAO;
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
    std::vector<std::shared_ptr<Texture>> mTextures;
};

#endif // MESH_H
