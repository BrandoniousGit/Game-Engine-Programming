#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "sys/Exception.h"

namespace rend
{

Texture::Texture()
{
  resize(2, 2);
}

Texture::Texture(const Texture& _copy) :
  m_dirty(true),
  m_size(_copy.m_size),
  m_raw(_copy.m_raw)
{ }

Texture& Texture::operator=(const Texture& _other)
{
  m_dirty = true;
  m_size = _other.m_size;
  m_raw = _other.m_raw;

  return *this;
}

Texture::~Texture()
{
  if(m_id)
  {
    glDeleteTextures(1, &m_id);
  }
}

Texture::Texture(const sys::String& _path)
{
  load(_path);
}

Texture::Texture(int _width, int _height)
{
  resize(_width, _height);
}

void Texture::resize(int _width, int _height)
{
  m_dirty = true;
  m_size.x = _width;
  m_size.y = _height;
  m_raw.resize(_width * _height * 4);
}

void Texture::load(const sys::String& _path)
{
  m_dirty = true;
  m_raw.clear();

  stbi_set_flip_vertically_on_load(1);
  stbi_uc *data = stbi_load(_path.unsafe_raw(), &m_size.x, &m_size.y, NULL, 4);

  if(!data)
  {
    throw sys::Exception("Failed to load texture");
  }

  m_raw.resize(m_size.x * m_size.y * 4);

  for(size_t ci = 0; ci < m_raw.size(); ++ci)
  {
    m_raw[ci] = data[ci];
  }

  free(data);
}

GLuint Texture::id()
{
  if(!m_id)
  {
    glGenTextures(1, &m_id);

    if(!m_id)
    {
      throw sys::Exception("Failed to allocate texture");
    }
  }

  if(m_dirty)
  {
    m_dirty = false;
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.x, m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, &m_raw[0]);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  return m_id;
}

ivec2 Texture::size() const
{
  return m_size;
}

}

