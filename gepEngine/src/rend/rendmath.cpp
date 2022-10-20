#include "rendmath.h"

namespace rend
{

mat4 rotate_xyz(const mat4& _m, const vec3& _angle)
{
  mat4 rtn(_m);

  rtn = rend::rotate(rtn, rend::radians(_angle.y), vec3(0, 1, 0));
  rtn = rend::rotate(rtn, rend::radians(_angle.x), vec3(1, 0, 0));
  rtn = rend::rotate(rtn, rend::radians(_angle.z), vec3(0, 0, 1));

  return rtn;
}

}

