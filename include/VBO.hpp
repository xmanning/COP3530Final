#pragma once
#include "Common.hpp"
#include <glm/glm.hpp>
#include <vector>
class VBO
{
    GLuint id;
    GLenum target;
    bool dynamic;
public:
    VBO() {};
    VBO(GLenum target, bool dynamic);
    void Bind();
    void Buffer(std::vector<glm::vec3> data);
};