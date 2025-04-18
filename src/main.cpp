#include "Application.hpp"
#include "RayTests.h"
using namespace glm;

int main()
{ 
    Application app = Application("Project 3");
    app.Start();
    return 0;
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
  float tmin = max(xmin,ymin);
  float tmax = min(xmax,ymax); // tightens values instead of checking both against z. Essentially if the bigger one fails, why bother checking the smaller one.

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

  vec3 normal = normalize(cross((b-a), (c-a))); // Gets the normal vector of the triangle.
  float d = dot(normal, a);
  if(dot(normal, direction)==0) return false;
  float rdist = d/(dot(normal, direction));
  result+=direction*rdist;
  result+=origin; // Adding it back now.
  return true;

}
