#include <GL/glew.h>

#include "sys/String.h"
#include "sys/Ptr.h"
#include "sys/Zero.h"

namespace rend
{

struct Shader : sys::EnablePtr
{
  Shader(const sys::String& _vertPath, const sys::String& _fragPath);
  ~Shader();

  GLuint id();
  GLint projectionLoc();
  GLint modelLoc();
  GLint viewLoc();
  GLint texture0Loc();
  GLint texture1Loc();
  GLint colorLoc();

private:
  sys::Zero<GLuint> m_id;
  sys::Zero<GLint> m_projectionLoc;
  sys::Zero<GLint> m_viewLoc;
  sys::Zero<GLint> m_modelLoc;
  sys::Zero<GLint> m_texture0Loc;
  sys::Zero<GLint> m_texture1Loc;
  sys::Zero<GLint> m_colorLoc;

  sys::String m_vertSrc;
  sys::String m_fragSrc;

  Shader(const Shader& _copy);
  Shader& operator=(const Shader& _other);

};

}
