#include "VAO.hpp"

VAO::VAO()
{
    glGenVertexArrays(1, &this->id);
}
void VAO::Bind()
{
    glBindVertexArray(this->id);
}
void VAO::Attribute(VBO* vbo, int index, size_t size, GLenum type, int stride, int offset)
{
    this->Bind();
	vbo->Bind();
    switch (type) {
    case GL_BYTE:
    case GL_UNSIGNED_BYTE:
    case GL_SHORT:
    case GL_UNSIGNED_SHORT:
    case GL_INT:
    case GL_UNSIGNED_INT:
    case GL_INT_2_10_10_10_REV:
    case GL_UNSIGNED_INT_2_10_10_10_REV:
        glVertexAttribIPointer(index, size, type, stride, (void*)offset);
        break;
    default:
        glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)offset);
        break;
    }
    glEnableVertexAttribArray(index);
}