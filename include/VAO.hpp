#pragma once
#include "VBO.hpp"

class VAO
{
GLuint id;
public:
VAO();
void Bind();
void Attribute(VBO* vbo, int index, size_t size, GLenum type, int stride, int offset);
};