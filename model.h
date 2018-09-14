#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class Model
{
public:
    Model(const std::string &path);

    void draw(Shader &shader);

private:
    void loadModel(const std::string &path);
    void processNode(aiNode *node, const aiScene *scene);
    std::unique_ptr<Mesh> processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<std::shared_ptr<Texture>> loadMaterialTexture(aiMaterial *material, aiTextureType type, std::string typeName);

private:
    std::vector<std::unique_ptr<Mesh>> mMeshes;
    std::vector<std::shared_ptr<Texture>> mLoadedTextures;
    std::string mDirectory;
};

#endif // MODEL_H
