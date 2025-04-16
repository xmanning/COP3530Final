#pragma once
#include "Common.hpp"
#include <glm/glm.hpp>
#include "ViewProjection.hpp"
class Shader
{
unsigned int id;
public:
    Shader(const char* frag_path, const char* vert_path);
    void Use();
    void UniformFloat(char* name, float value);
    void UniformVec2(char* name, glm::vec2 value);
    void UniformVec3(char* name, glm::vec3 value);
    void UniformVec4(char* name, glm::vec4 value);
    void UniformInt(char* name, int value);
    void UniformIvec2(char* name, glm::ivec2 value);
    void UniformIvec3(char* name, glm::ivec3 value);
    void UniformIvec4(char* name, glm::ivec4 value);
    void UniformMat2(char* name, glm::mat2 value);
    void UniformMat3(char* name, glm::mat3 value);
    void UniformMat4(char* name, glm::mat4 value);
    void UniformViewProjection(ViewProjection vp);
};