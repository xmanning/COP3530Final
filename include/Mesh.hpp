#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <VAO.hpp>
#include <VBO.hpp>
class Mesh
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    VBO* vbo;
    VAO* vao;
    public:
        Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals);
        void Render();
        
};