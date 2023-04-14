#include <filesystem>
#include <fstream>
#include "Mesh.hpp"

class Model
{
public:
    Model() = delete;
    Model(std::string path);
    Model(const Model& other) = delete;
    Model(Model&& other) = delete;
    Model& operator=(Model other) = delete;
    ~Model() = default;

private:
    void LoadModel(std::string& modelFile);
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(const char* name, aiMesh* mesh, const aiScene* scene);

private:
    std::vector<Mesh> meshes;
};