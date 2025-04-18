#include "BVH.h"
#include "RayTests.h"

int BVH::maxTriangles = 1024;

bool BVH::BoundingBox::Contains(vec3 point) const
{
    return min.x <= point.x && min.y <= point.y && min.z <= point.z && max.x >= point.x && max.y >= point.y && max.z >= point.z;
}

void BVH::BoundingBox::GrowToInclude(vec3 point)
{
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
        Node* correctChild;
        if (splitAxis == 0)
        {
            correctChild = (max.x - t.center.x) < (min.x - t.center.x) ? childA : childB;
        }
        else if (splitAxis == 1)
        {
            correctChild = (max.y - t.center.y) < (min.y - t.center.y) ? childA : childB;
        }
        else
        {
            correctChild = (max.z - t.center.z) < (min.z - t.center.z) ? childA : childB;
        }
        correctChild->AddTriangle(t);
    } else
    {
        triangles.push_back(t);
        bounds.GrowToInclude(t.a);
        bounds.GrowToInclude(t.b);
        bounds.GrowToInclude(t.c);
        if (triangles.size() > maxTriangles)
        {
            Split();
        }
    }
}

void BVH::Node::Split()
{
    // split
    vec3 size = bounds.max - bounds.min;
    float largestAxis = glm::max(size.x, glm::max(size.y, size.z));
    if (largestAxis == size.x) splitAxis = 0;
    else if(largestAxis == size.y) splitAxis = 1;
    else splitAxis = 2;

    for(Triangle& t : triangles)
    {
        Node* correctChild;
        if (splitAxis == 0)
        {
            correctChild = (max.x - t.center.x) < (min.x - t.center.x) ? childA : childB;
        }
        else if (splitAxis == 1)
        {
            correctChild = (max.y - t.center.y) < (min.y - t.center.y) ? childA : childB;
        }
        else
        {
            correctChild = (max.z - t.center.z) < (min.z - t.center.z) ? childA : childB;
        }
        correctChild->AddTriangle(t);
    }

    // then clear the triangles to save memory
    triangles.clear();
}

bool BVH::Node::TestRay(vec3 origin, vec3 direction, vec3 &hitPoint, vector<BoundingBox> &hitBoxes)
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
                    return true;
                }
            }
        } else
        {
            if(childA->TestRay(origin, direction, hitPoint, hitBoxes))
            {
                return true;
            }
            if(childB->TestRay(origin, direction, hitPoint, hitBoxes))
            {
                return true;
            }
        }
        return false;
    }
    return false;
}


bool BVH::TestRay(vec3 origin, vec3 direction, vec3 &hitPoint, vector<BoundingBox> &hitBoxes)
{
    root->TestRay(origin, direction, hitPoint, hitBoxes);
}


BVH::BVH(Mesh& mesh)
{
    auto vertices = mesh.getVertices();
    for(int i = 0; i < vertices.size() / 3; i += 3)
    {
        root->AddTriangle(Triangle(vertices[i], vertices[i + 1], vertices[i+2]));
    }
}
