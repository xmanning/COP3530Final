#include <glm/glm.hpp>
#include <Mesh.hpp>
#include <vector>
#include <limits>
#pragma once

using namespace glm;
using namespace std;

class BVH
{
    public:

    struct BoundingBox
    {
        vec3 min = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
        vec3 max = {std::numeric_limits<float>::min(),std::numeric_limits<float>::min(),std::numeric_limits<float>::min()};
        bool Contains(vec3 point) const;
        void GrowToInclude(vec3 point);
    };

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

    struct Node
    {
        int depth = 0;
        BoundingBox bounds;
        vector<Triangle> triangles;
        Node* childA;
        Node* childB;
        int splitAxis; // x = 0, y = 1, z = 2
        float splitPos;
		void AddTriangle(Triangle t);
        void Split();
        bool TestRay(vec3 origin, vec3 direction, vec3& hitPoint, BVH::Triangle& hitTriangle, vector<BoundingBox>& hitBoxes);
    };

    bool TestRay(vec3 origin, vec3 direction, vec3& hitPoint, BVH::Triangle& hitTriangle, vector<BoundingBox>& hitBoxes);
    BVH(Mesh& mesh);
    BoundingBox& getBounds();
    Node* getRoot();
    static int maxTriangles;
    static int maxDepth;
    
    private:
    Node* root = new Node();

};