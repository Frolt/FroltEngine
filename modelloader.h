#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <vector>
#include <string>
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "meshfactory.h"

class ModelLoader
{
public:
    ModelLoader(const std::string &path);

private:
    void loadModel(const std::string &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTexture(aiMaterial *material, aiTextureType type, std::string typeName);

public:
    std::vector<Mesh> mMeshes;
private:
    std::vector<Texture> mLoadedTextures;
    std::string mDirectory;
};

#endif // MODELLOADER_H