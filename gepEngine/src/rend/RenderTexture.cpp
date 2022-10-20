#include "RenderTexture.h"

#include "sys/Exception.h"

namespace rend
{

RenderTexture::RenderTexture() :
  m_size(32, 32),
  m_texture(m_size.x, m_size.y)
{ }

RenderTexture::RenderTexture(int _width, int _height) :
  m_size(power_of_two(_width), power_of_two(_height)),
  m_texture(m_size.x, m_size.y)
{ }

RenderTexture::~RenderTexture()
{
  if(m_fboId)
  {
    glDeleteFramebuffers(1, &m_fboId);
    glDeleteRenderbuffers(1, &m_rboId);
  }
}

void RenderTexture::bind()
{
  texture();
  glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
}

void RenderTexture::unbind() const
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

sys::Ptr<Texture> RenderTexture::texture()
{
  if(!m_fboId)
  {
    glGenFramebuffers(1, &m_fboId);
    if(!m_fboId) throw sys::Exception("Failed to allocate frame buffer");
    glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);

    //glGenTextures(1, &m_texId);
    //if(!m_texId) throw sys::Exception("Failed to allocate texture");
    glBindTexture(GL_TEXTURE_2D, m_texture.id());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.x, m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenRenderbuffers(1, &m_rboId);
    if(!m_rboId) throw sys::Exception("Failed to allocate render buffer");
    glBindRenderbuffer(GL_RENDERBUFFER, m_rboId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_size.x, m_size.y);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texId, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture.id(), 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboId);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  return &m_texture;
}

ivec2 RenderTexture::size() const
{
  return m_size;
}

int RenderTexture::power_of_two(int _input) const
{
  int rtn = 1;

  while(rtn < _input)
  {
    rtn *= 2;
  }

  return rtn;
}

}

