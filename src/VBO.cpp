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

void VBO::Buffer(std::vector<glm::vec3> data)
{
    this->Bind();
    glBufferData(this->target, data.size() * sizeof(float) * 3, data.data(), this->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}