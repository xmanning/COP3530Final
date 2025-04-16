#include <VBO.hpp>

VBO::VBO(GLenum target, bool dynamic)
{
    glGenBuffers(1, &this->id);
    this->target = target;
    this->dynamic = dynamic;
}

void VBO::Bind()
{
    glBindBuffer(this->target, this->id);
}

void VBO::Buffer(void* data, size_t size)
{
    this->Bind();
    glBufferData(this->target, size, data, this->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void VBO::Buffer(std::vector<float> data)
{
    this->Bind();
    glBufferData(this->target, data.size() * sizeof(float), data.data(), this->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void VBO::Buffer(std::vector<int> data)
{
    this->Bind();
    glBufferData(this->target, data.size() * sizeof(int), data.data(), this->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void VBO::Buffer(std::vector<unsigned int> data)
{
    this->Bind();
    glBufferData(this->target, data.size() * sizeof(int), data.data(), this->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

