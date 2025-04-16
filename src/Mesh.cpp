#include "Mesh.hpp"

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals)
{
    this->vertices = vertices;
    this->normals = normals;
    vbo = new VBO(GL_VERTEX_ARRAY, false);
    vao = new VAO();
    vao->Attribute(vbo, 0, 3, GL_FLOAT, sizeof(float) * 6, 0);
    vao->Attribute(vbo, 1, 3, GL_FLOAT, sizeof(float) * 6, sizeof(float) * 3);
}

void Mesh::Render()
{
    vbo->Bind();
    vao->Bind();
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices));
}