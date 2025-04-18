#pragma once
#include <glm/glm.hpp>
using namespace glm;

bool IntersectRayBox(vec3 origin, vec3 direction, vec3 boxMin, vec3 boxMax);
bool IntersectRayTriangle(vec3 origin, vec3 direction, vec3 a, vec3 b, vec3 c, vec3& result);