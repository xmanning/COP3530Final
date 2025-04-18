#include "Mesh.hpp"

Mesh::Mesh(std::string path)
{
    std::ifstream file(path);
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<int> indices;
    std::vector<int> normalIndices;

    std::string buffer;
    while(std::getline(file, buffer))
    {
        std::stringstream ss(buffer);
        std::string dataType;
        ss >> dataType;
        if(dataType == "v")
        {
            float x, y, z;
            ss >> x;
            ss >> y;
            ss >> z;
            vertices.push_back({x,y,z});
        }
        else if(dataType == "vn")
        {
            float x, y, z;
            ss >> x;
            ss >> y;
            ss >> z;
            normals.push_back({x,y,z});
        }
        else(dataType == "f")
        {
            for(int i = 0; i < 3; i++)
            {
                int index;
                ss >> index;
                indices.push_back(index);
                ss.ignore();
                ss >> index;
                normalIndices.push_back(index);
                ss.ignore();
                ss >> index;
            }
        }
    }
    file.close();

    for(int index : indices)
    {
        this->vertices.push_back(vertices[index]);
    }
    for(int index : normalIndices)
    {
        this->normals.push_back(normals[index]);
    }

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

std::vector<glm::vec3>& Mesh::getVertices()
{
    return this->vertices;
}