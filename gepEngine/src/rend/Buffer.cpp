#include "Buffer.h"

#include "sys/Exception.h"

namespace rend
{

Buffer::Buffer() :
  m_dirty(true)
{ }

Buffer::Buffer(const Buffer& _copy) :
  m_dirty(true),
  m_components(_copy.m_components),
  m_data(_copy.m_data)
{ }

Buffer& Buffer::operator=(const Buffer& _other)
{
  m_dirty = true;
  m_components = _other.m_components;
  m_data = _other.m_data;

  return *this;
}

Buffer::~Buffer()
{
  if(m_id)
  {
    glDeleteBuffers(1, &m_id);
  }
}

GLuint Buffer::id()
{
  if(!m_id)
  {
    glGenBuffers(1, &m_id);

    if(!m_id) throw sys::Exception("Failed to allocate buffer");
  }

  if(m_dirty)
  {
    m_dirty = false;
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, m_data.size() * sizeof(m_data[0]), &m_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  return m_id;
}

void Buffer::clear()
{
  m_components = 0;
  m_dirty = true;
  m_data.clear();
}

void Buffer::add(const vec2& _value)
{
  if(m_components != 0 && m_components != 2) throw sys::Exception("Mixed components unsupported");

  m_data.push(_value.x);
  m_data.push(_value.y);
  m_components = 2;
  m_dirty = true;
}

void Buffer::add(const vec3& _value)
{
  if(m_components != 0 && m_components != 3) throw sys::Exception("Mixed components unsupported");

  m_data.push(_value.x);
  m_data.push(_value.y);
  m_data.push(_value.z);
  m_components = 3;
  m_dirty = true;
}

void Buffer::add(float _value)
{
  if(m_components != 0 && m_components != 1) throw sys::Exception("Mixed components unsupported");

  m_data.push(_value);
  m_components = 1;
  m_dirty = true;
}

int Buffer::components() const
{
  if(!m_components) throw sys::Exception("No current data");

  return (int)m_components;
}

size_t Buffer::size() const
{
  return m_data.size();
}

bool Buffer::dirty() const
{
  return m_dirty;
}

}

