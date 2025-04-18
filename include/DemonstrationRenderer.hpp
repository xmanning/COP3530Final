#pragma once
#include "Shader.hpp"
#include "VAO.hpp"
#include <glm/glm.hpp>
#include "BVH.h"
class DemonstrationRenderer
{
    Shader* shader;
    VBO* vbo;
    VAO* vao;
    public:
    DemonstrationRenderer();
    ~DemonstrationRenderer();
    void DrawBox(BVH::BoundingBox box);
    void SetColor(glm::vec3 color);
    void DrawPoints(std::vector<glm::vec3> points);
    void DrawLines(std::vector<glm::vec3> lines);
    void DrawTriangle(BVH::Triangle tri);
    void DrawBVHNode(BVH::Node* node);
    void DrawRay(glm::vec3 origin, glm::vec3 direction);

};
