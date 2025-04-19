#include "Application.hpp"
#include <algorithm>
#include <limits>
int main()
{ 
    Application app = Application("Project 3");
    app.Start();
    return 0;
}

float RayBoundingBoxDistance(vec3 origin, vec3 direction, vec3 boxMin, vec3 boxMax)
{
  vec3 invDir = vec3(1.0f / direction.x, 1.0f / direction.y, 1.0f / direction.z);
  vec3 tMin = (boxMin - origin) * invDir;
  vec3 tMax = (boxMax - origin) * invDir;
  vec3 t1 = min(tMin, tMax);
  vec3 t2 = max(tMin, tMax);
  float tNear = glm::max(glm::max(t1.x, t1.y), t1.z);
  float tFar = glm::min(glm::min(t2.x, t2.y), t2.z);

  bool hit = tFar >= tNear && tFar > 0;
  float dst = hit ? tNear > 0 ? tNear : 0 : std::numeric_limits<float>::infinity();
  return dst;
}

bool IntersectRayBox(vec3 origin, vec3 direction, vec3 boxMin, vec3 boxMax) {
  boxMin-=origin; // essentially centers calculations on 0,0,0 meaning we can ignore the origin for the rest of the calculation.
  boxMax-=origin;

  float xmin = boxMin.x/direction.x;
  float xmax = boxMax.x/direction.x;
  if(xmin>xmax) { // Switches them around if the box is "upside down".
    float temp = xmin;
    xmin = xmax;
    xmax = temp;
  }

  float ymin = boxMin.y/direction.y;
  float ymax = boxMax.y/direction.y;
  if(ymin>ymax) {
    float temp = ymin;
    ymin=ymax;
    ymax=temp;
  }

  if(xmin>ymax || ymin>xmax) return false; // If the minimum value for one plane is > the max for another, it means the ray is outside the bounding box.
  float tmin = glm::max(xmin,ymin);
  float tmax = glm::min(xmax,ymax); // tightens values instead of checking both against z. Essentially if the bigger one fails, why bother checking the smaller one.

  float zmin = boxMin.z/direction.z;
  float zmax = boxMax.z/direction.z;
  if(zmin>zmax) {
    float temp = zmin;
    zmin=zmax;
    zmax=temp;
  }
  if(tmin>zmax||zmin>tmax) return false; // If either x or y is outside the bounding box when compared with z.
  return true;
  
}

bool IntersectRayTriangle(vec3 origin, vec3 direction, vec3 a, vec3 b, vec3 c, vec3& result) {
  a-=origin; // No one likes the origin. We will add it back when we find the result.
  b-=origin;
  c-=origin;

  vec3 normal = glm::normalize(glm::cross((b-a), (c-a))); // Gets the normal vector of the triangle.
  float d = glm::dot(normal, a);
  if(glm::dot(normal, direction)==0) return false;
  float rdist = d/(glm::dot(normal, direction));
  vec3 plane_int = direction*rdist; // The point the ray intercepts the plane at.
  if(glm::dot(glm::cross((b-a), (plane_int-a)), normal)<0) return false; // Checks that the actual 
  if(glm::dot(glm::cross((c-b), (plane_int-b)), normal)<0) return false;
  if(glm::dot(glm::cross((a-c), (plane_int-c)), normal)<0) return false;

  result=plane_int;
  result+=origin; // Adding it back now.
  return true;

}