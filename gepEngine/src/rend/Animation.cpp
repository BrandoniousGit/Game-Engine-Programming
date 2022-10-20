#include "Animation.h"
#include "Model.h"

namespace rend
{

Animation::Animation() :
  m_frames(1)
{ }

sys::Ptr<Frame> Animation::frame(int _frame)
{
  _frame = _frame % m_frames.size();

  return &m_frames[_frame];
}

sys::Ptr<Transform> Frame::transform(Part& _part, bool _add)
{
  sys::Ptr<Transform> rtn(transform(_part));

  if(rtn) return rtn;
  if(!_add) return NULL;

  rtn = m_transforms.push(Transform());
  rtn->part = &_part;
  rtn->scale = vec3(1, 1, 1);

  return rtn;
}

sys::Ptr<Transform> Frame::transform(const Part& _part)
{
  sys::Ptr<const Part> part(&_part);

  for(size_t ti = 0; ti < m_transforms.size(); ++ti)
  {
    if(m_transforms[ti].part == part)
    {
      return &m_transforms[ti];
    }
  }

  return NULL;
}

mat4 Animation::model(const Part& _part, float _frame)
{
  //rend::mat4 model = glm::translate(rend::mat4(1.0f), _part.offset);
  sys::Ptr<rend::Transform> t = frame((int)_frame)->transform(_part);
  if(!t) return mat4(1.0f);

  rend::mat4 model(1.0f);
  model = rend::translate(model, _part.offset);
  model = rend::translate(model, t->translation);

  model = rend::rotate(model, rend::radians(t->rotation.y), rend::vec3(0, 1, 0));
  model = rend::rotate(model, rend::radians(t->rotation.x), rend::vec3(1, 0, 0));
  model = rend::rotate(model, rend::radians(t->rotation.z), rend::vec3(0, 0, 1));

  //model *= toMat4(t->rot);

  model = rend::translate(model, -_part.offset);
  model = rend::scale(model, t->scale);

  return model;
}

}

