#include <glm/glm.hpp>
#include <Mesh.hpp>
#include <vector>
#pragma once

using namespace glm;
using namespace std;

class BVH
{
    struct Triangle
    {
        vec3 a;
        vec3 b;
        vec3 c;
        vec3 center;

        Triangle(vec3 a, vec3 b, vec3 c)
        {
            this->a = a;
            this->b = b;
            this->c = c;
            this->center = (a+b+c)/3.0f;
        }
    };
    struct BoundingBox
    {
        vec3 min;
        vec3 max;
        bool Contains(vec3 point) const;
        void GrowToInclude(vec3 point);
    };
    struct Node
    {
        BoundingBox bounds;
        vector<Triangle> triangles;
        Node* childA;
        Node* childB;
        int splitAxis; // x = 0, y = 1, z = 2
		void AddTriangle(Triangle t);
        void Split();
        bool TestRay(vec3 origin, vec3 direction, vec3& hitPoint, vector<BoundingBox>& hitBoxes);
    };

    Node* root = new Node();
    static int maxTriangles;
    public:
    bool TestRay(vec3 origin, vec3 direction, vec3& hitPoint, vector<BoundingBox>& hitBoxes);
    BVH(Mesh& mesh);
};