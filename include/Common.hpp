#include "assimp/scene.h"
#include "glm/glm.hpp"

inline glm::vec3 aiToGLM(aiVector3D& ai)
{
    glm::vec3 temp;
    temp.x = ai.x;
    temp.y = ai.y;
    temp.z = ai.z;
    return temp;
}

inline glm::vec2 aiToGLM(aiVector2D& ai)
{
    glm::vec2 temp;
    temp.x = ai.x;
    temp.y = ai.y;
    return temp;
}