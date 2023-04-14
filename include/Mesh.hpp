#include "glm/glm.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include <vector>

struct AABB
{
    glm::vec3 min;
    glm::vec3 max;
};

struct MeshVariables
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

struct Mesh
{
    std::string nodeName;
    std::string meshName;

    std::vector<MeshVariables> variables;
    std::vector<unsigned int> indices;

    AABB aabb;
};