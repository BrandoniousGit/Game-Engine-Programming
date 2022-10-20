#include "rendmath.h"

#include <GL/glew.h>

#include "sys/Ptr.h"
#include "sys/Zero.h"
#include "sys/Vector.h"

namespace rend
{

struct Mesh;
struct Buffer;

struct Buffer : sys::EnablePtr
{
  Buffer();
  ~Buffer();
  Buffer(const Buffer& _copy);
  Buffer& operator=(const Buffer& _other);

  void add(float _value);
  void add(const vec2& _value);
  void add(const vec3& _value);

  int components() const;
  size_t size() const;
  void clear();

private:
  friend struct Mesh;

  sys::Zero<GLuint> m_id;
  sys::Zero<bool> m_dirty;
  sys::Zero<size_t> m_components;
  sys::Vector<float> m_data;

  GLuint id();
  bool dirty() const;

};

}

