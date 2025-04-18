#include "DemonstrationRenderer.hpp"
#include "Application.hpp"

DemonstrationRenderer::DemonstrationRenderer()
{
    shader = new Shader("res/debug.frag", "res/debug.vert");
    vao = new VAO();
    vbo = new VBO(GL_ARRAY_BUFFER, true);
    vao->Attribute(vbo, 0, 3, GL_FLOAT, sizeof(float) * 3, 0);
}

DemonstrationRenderer::~DemonstrationRenderer()
{
    delete shader;
    delete vbo;
    delete vao;
}

void DemonstrationRenderer::SetColor(glm::vec3 color)
{
    shader->UniformVec3("color", color);
}

void DemonstrationRenderer::DrawLines(std::vector<glm::vec3> lines)
{
    vbo->Buffer(lines);
    shader->Use();
    vao->Bind();
    shader->UniformViewProjection(Application::instance->GetCamera()->GetViewProjection());
    glDrawArrays(GL_LINES, 0, lines.size());   
}

void DemonstrationRenderer::DrawPoints(std::vector<glm::vec3> points)
{
    vbo->Buffer(points);
    shader->Use();
    vao->Bind();
    shader->UniformViewProjection(Application::instance->GetCamera()->GetViewProjection());
    glDrawArrays(GL_POINTS, 0, points.size());   
}

void DemonstrationRenderer::DrawBVHNode(BVH::Node* node)
{
    
    if (node->childA != nullptr && node->childB != nullptr)
    {
        DrawBVHNode(node->childA);
        DrawBVHNode(node->childB);
    } else {
        DrawBox(node->bounds);
    }
}

void DemonstrationRenderer::DrawTriangle(BVH::Triangle tri)
{
    std::vector<glm::vec3> points = {tri.a, tri.b, tri.c};
    vbo->Buffer(points);
    shader->Use();
    vao->Bind();
    shader->UniformViewProjection(Application::instance->GetCamera()->GetViewProjection());
    glDrawArrays(GL_TRIANGLES, 0, points.size());   
}

void DemonstrationRenderer::DrawRay(glm::vec3 origin, glm::vec3 direction)
{
    DrawLines({origin, origin + direction * 5.0f});
}

void DemonstrationRenderer::DrawBox(BVH::BoundingBox box)
{
    glm::vec3 min = box.min;
    glm::vec3 max = box.max;
    glm::vec3 v0 = min;
    glm::vec3 v1 = {max.x, min.y, min.z};
    glm::vec3 v2 = {max.x, max.y, min.z};
    glm::vec3 v3 = {min.x, max.y, min.z};
    glm::vec3 v4 = {min.x, min.y, max.z};
    glm::vec3 v5 = {max.x, min.y, max.z};
    glm::vec3 v6 = max;
    glm::vec3 v7 = {min.x, max.y, max.z};
    std::vector<glm::vec3> points = {
        v0, v1,
        v1, v2,
        v2, v3,
        v3, v0, 
        v4, v5,
        v5, v6,
        v6, v7,
        v7, v4,
        v0, v4,
        v1, v5,
        v2, v6,
        v3, v7,
    };
    DrawLines(points);
}

