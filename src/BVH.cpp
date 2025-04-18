#include "BVH.h"
#include "RayTests.h"
#include <iostream>
int BVH::maxTriangles = 128;
int BVH::maxDepth = 15;
bool BVH::BoundingBox::Contains(vec3 point) const
{
    return min.x <= point.x && min.y <= point.y && min.z <= point.z && max.x >= point.x && max.y >= point.y && max.z >= point.z;
}

void BVH::BoundingBox::GrowToInclude(vec3 point)
{
    if(min.x == std::numeric_limits<float>::max())
    {
        min = point;
        max = point;
        return;
    }

    min.x = glm::min(point.x, min.x);
    min.y = glm::min(point.y, min.y);
    min.z = glm::min(point.z, min.z);
    max.x = glm::max(point.x, max.x);
    max.y = glm::max(point.y, max.y);
    max.z = glm::max(point.z, max.z);
}



void BVH::Node::AddTriangle(Triangle t)
{
    if(childA != nullptr)
    {
        Node* correctChild = t.center[splitAxis] < splitPos ? childA : childB;
        correctChild->AddTriangle(t);
    } else
    {
        triangles.push_back(t);
        int triCount = triangles.size();
        if (triCount > maxTriangles && depth < maxDepth)
        {
            std::cout << "split\n";
            Split();
        }
    }
    bounds.GrowToInclude(t.a);
    bounds.GrowToInclude(t.b);
    bounds.GrowToInclude(t.c);
}

void BVH::Node::Split()
{
    // split
    childA = new Node();
    childA->depth = depth + 1;
    childB = new Node();
    childB->depth = depth + 1;
    vec3 size = bounds.max - bounds.min;
    float largestAxis = glm::max(size.x, glm::max(size.y, size.z));
    if (largestAxis == size.x) splitAxis = 0;
    else if(largestAxis == size.y) splitAxis = 1;
    else splitAxis = 2;
    splitPos = (bounds.max + bounds.min)[splitAxis] / 2.0f;

    for(Triangle& t : triangles)
    {
        Node* correctChild = t.center[splitAxis] < splitPos ? childA : childB;
        correctChild->AddTriangle(t);
    }

    // then clear the triangles to save memory
    triangles.clear();
}

bool BVH::Node::TestRay(vec3 origin, vec3 direction, vec3 &hitPoint, BVH::Triangle& hitTriangle, vector<BoundingBox> &hitBoxes)
{
    if (IntersectRayBox(origin, direction, bounds.min, bounds.max))
    {
        hitBoxes.push_back(bounds);
        if (childA == nullptr)
        {
            for(Triangle& tri : triangles)
            {
                if (IntersectRayTriangle(origin, direction, tri.a, tri.b, tri.c, hitPoint))
                {
                    hitTriangle = tri;
                    return true;
                }
            }
        } else
        {
            if(childA->TestRay(origin, direction, hitPoint, hitTriangle, hitBoxes))
            {
                return true;
            }
            if(childB->TestRay(origin, direction, hitPoint, hitTriangle, hitBoxes))
            {
                return true;
            }
        }
        return false;
    }
    return false;
}


bool BVH::TestRay(vec3 origin, vec3 direction, vec3 &hitPoint, BVH::Triangle& hitTriangle, vector<BoundingBox> &hitBoxes)
{
    root->TestRay(origin, direction, hitPoint, hitTriangle, hitBoxes);
}

BVH::BoundingBox& BVH::getBounds()
{
    return root->bounds;
}

BVH::Node* BVH::getRoot()
{
    return root;
}

BVH::BVH(Mesh& mesh)
{
    auto vertices = mesh.getVertices();
    int i = 0;
    while (i < vertices.size())
    {
        root->AddTriangle(Triangle(vertices[i], vertices[i + 1], vertices[i+2]));
        i += 3;
    }
}
