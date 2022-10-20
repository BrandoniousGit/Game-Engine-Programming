#include "rendmath.h"
#include "Texture.h"

#include <GL/glew.h>

#include "sys/Zero.h"
#include "sys/Ptr.h"

namespace rend
{

struct RenderTexture : sys::EnablePtr
{
  RenderTexture();
  RenderTexture(int _width, int _height);
  ~RenderTexture();

  void bind();
  void unbind() const;

  sys::Ptr<Texture> texture();
  ivec2 size() const;

private:
  sys::Zero<GLuint> m_fboId;
  sys::Zero<GLuint> m_rboId;
  ivec2 m_size;
  Texture m_texture;

  int power_of_two(int _input) const;

};

}

