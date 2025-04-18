#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <VAO.hpp>
#include <VBO.hpp>
#include <string>
#include <fstream>
#include <sstream>
class Mesh
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    VBO* vbo;
    VAO* vao;
    public:
        Mesh(std::string path);
        void Render();
        std::vector<glm::vec3>& getVertices();
};