#include "Model.hpp"
#include "Common.hpp"

#include <iostream>

Model::Model(std::string path)
{
    LoadModel(path);
}

void Model::LoadModel(std::string& modelFile)
{
    if(!std::filesystem::exists(modelFile))
    {
        std::cout << modelFile + " is not found";
        exit(-1);
    }

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(modelFile, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "Scene cannot load\n";
        std::cout << importer.GetErrorString() << "\n";
        exit(-1);
    }

    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    aiMesh* mesh = nullptr;

    for(int i = 0; i < node->mNumMeshes; i++)
    {
        mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(node->mName.C_Str(), mesh, scene));
    }

    for(int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(const char* name, aiMesh* mesh, const aiScene* scene)
{
    unsigned int size = mesh->mNumVertices;
    MeshVariables meshVar;

    Mesh tempMesh;
    tempMesh.nodeName = std::string(name);
    tempMesh.meshName = std::string(mesh->mName.C_Str());
    tempMesh.aabb.min = aiToGLM(mesh->mAABB.mMin);
    tempMesh.aabb.max = aiToGLM(mesh->mAABB.mMax);
    tempMesh.variables.resize(size);

    for(unsigned int i = 0; i < size; i++)
    {
        meshVar.position = aiToGLM(mesh->mVertices[i]);

        if(mesh->HasNormals())
        {
            meshVar.normal = aiToGLM(mesh->mNormals[i]);
        }

        if(mesh->mTextureCoords[0])
        {
            meshVar.texCoords = aiToGLM(mesh->mTextureCoords[0][i]);
            meshVar.tangent = aiToGLM(mesh->mTangents[i]);
            meshVar.bitangent = aiToGLM(mesh->mBitangents[i]);
        }
        else
        {
            meshVar.texCoords = glm::vec2(0.0f, 0.0f);
        }

        tempMesh.variables[i] = meshVar;
    }

    aiFace face;

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        face = mesh->mFaces[i];

        for(unsigned int j = 0; j < face.mNumIndices; j++)
        {
            tempMesh.indices.push_back(face.mIndices[j]);
        }
    }

    return tempMesh;
}