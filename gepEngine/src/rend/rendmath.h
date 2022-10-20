#ifndef REND_MATH_H
#define REND_MATH_H

#define GLM_FORCE_CTOR_INIT
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/intersect.hpp"

namespace rend
{

using namespace glm;

struct Ray
{
  vec3 origin;
  vec3 direction;
};

struct Triangle
{
  vec3 a;
  vec3 b;
  vec3 c;
};

mat4 rotate_xyz(const mat4& _m, const vec3& _angle);

}

#endif

