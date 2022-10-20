#ifndef REND_TEXTURE_H
#define REND_TEXTURE_H

#include "rendmath.h"

#include <GL/glew.h>

#include "sys/Zero.h"
#include "sys/Ptr.h"
#include "sys/Vector.h"
#include "sys/String.h"

namespace rend
{

struct Texture : sys::EnablePtr
{
  Texture();
  Texture(const Texture& _copy);
  Texture& operator=(const Texture& _other);
  ~Texture();

  Texture(const sys::String& _path);
  Texture(int _width, int _height);

  void resize(int _width, int _height);
  void load(const sys::String& _path);
  GLuint id();

  ivec2 size() const;

private:
  sys::Zero<GLuint> m_id;
  sys::Zero<bool> m_dirty;
  ivec2 m_size;
  sys::Vector<unsigned char> m_raw;

};

}

#endif

