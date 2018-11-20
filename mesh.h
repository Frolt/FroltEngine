#ifndef MESH_H
#define MESH_H

#include <QOpenGLFunctions_4_1_Core>
#include <vector>
#include <memory>
#include "vertex.h"
#include "texture.h"
#include "shader.h"

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void draw(Shader &shader);
private:
    void setupMesh();

public:
    unsigned int mVAO;
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
    std::vector<Texture> mTextures;
    std::shared_ptr<QOpenGLFunctions_4_1_Core> gl = std::make_shared<QOpenGLFunctions_4_1_Core>();
};

#endif // MESH_H
