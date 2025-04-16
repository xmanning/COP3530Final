#pragma once
#include "Common.hpp"
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
    void Buffer(void* data, size_t size);
    void Buffer(std::vector<float> data);
    void Buffer(std::vector<int> data);
    void Buffer(std::vector<unsigned int> data);
};