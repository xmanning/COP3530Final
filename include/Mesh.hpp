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
    VBO* vbo;
    VAO* vao;
    unsigned int vertCount = 0;
    public:
        Mesh() {}
        Mesh(std::string path);
        void Render();
        std::vector<glm::vec3>& getVertices();
};