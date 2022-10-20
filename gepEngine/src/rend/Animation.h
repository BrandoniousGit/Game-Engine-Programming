#include "rendmath.h"

#include "sys/Vector.h"
#include "sys/Ptr.h"

namespace rend
{

struct Part;

struct Transform : sys::EnablePtr
{
  sys::Ptr<Part> part;
  vec3 translation;
  vec3 rotation;
  quat rot;
  vec3 scale;
};

struct Frame : sys::EnablePtr
{
  sys::Ptr<Transform> transform(Part& _part, bool _add);
  sys::Ptr<Transform> transform(const Part& _part);

private:
  sys::Vector<Transform> m_transforms;
};

struct Animation : sys::EnablePtr
{
  Animation();
  sys::Ptr<Frame> frame(int _frame);
  mat4 model(const Part& _part, float _frame);

private:
  sys::Vector<Frame> m_frames;

};

}

