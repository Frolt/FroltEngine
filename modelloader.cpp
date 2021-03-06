#include "modelloader.h"
#include "vertex.h"


ModelLoader::ModelLoader(const std::string &path)
{
    loadModel(path);
}

void ModelLoader::loadModel(const std::string &path)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        qWarning() << "ERROR::ASSIMP::" << importer.GetErrorString();
        return;
    }
    mDirectory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void ModelLoader::processNode(aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
        mMeshes.push_back(processMesh(scene->mMeshes[node->mMeshes[i]], scene));
    for (unsigned int i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene);
}

Mesh ModelLoader::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // Process vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vert;
        am::Vec3 temp;
        temp.x = mesh->mVertices[i].x;
        temp.y = mesh->mVertices[i].y;
        temp.z = mesh->mVertices[i].z;
        vert.mPosition = temp;
        temp.x = mesh->mNormals[i].x;
        temp.y = mesh->mNormals[i].y;
        temp.z = mesh->mNormals[i].z;
        vert.mNormal = temp;
        am::Vec2 texCoords;
        if (mesh->mTextureCoords[0]) {
            texCoords.x = mesh->mTextureCoords[0][i].x;
            texCoords.y = mesh->mTextureCoords[0][i].y;
        } else {
            texCoords.x = 0.0f;
            texCoords.y = 0.0f;
        }
        vert.mUV = texCoords;
        vertices.push_back(std::move(vert));
    }

    // Process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(std::move(face.mIndices[j]));
        }
    }

    // Process textures
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture> diffuseMaps = loadMaterialTexture(material, aiTextureType_DIFFUSE, "diffuseMap");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    std::vector<Texture> specularMaps = loadMaterialTexture(material, aiTextureType_SPECULAR, "specularMap");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    return Mesh{vertices, indices, textures};
}

std::vector<Texture> ModelLoader::loadMaterialTexture(aiMaterial *material, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
        aiString path;
        material->GetTexture(type, i, &path);
        bool skip = false;
        for (unsigned int j = 0; j < mLoadedTextures.size(); j++) {
            if (std::strcmp(mLoadedTextures[j].mPath.c_str(), path.C_Str()) == 0) {
                textures.push_back(mLoadedTextures[j]);
                skip = true;
                break;
            }
        }
        if (!skip) {
            Texture texture = Texture(mDirectory + "/" + path.C_Str());
            texture.mType = typeName;
            texture.mPath = path.C_Str();
            textures.push_back(texture);
            mLoadedTextures.push_back(texture);
        }
    }
    return textures;
}
