#include "Renderer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "RenderTexture.h"

#include <GL/glew.h>

#include "sys/Exception.h"

namespace rend
{

Renderer::Renderer(int _width, int _height) :
  m_projection(1.0f),
  m_view(1.0f),
  m_model(1.0f),
  m_clearColor(0.392f, 0.584f, 0.929f, 1.0f),
  m_color(1, 1, 1, 1),
  m_windowSize(_width, _height)
{ }

Renderer::Renderer(sys::Ptr<RenderTexture> _renderTexture) :
  m_renderTexture(_renderTexture),
  m_projection(1.0f),
  m_view(1.0f),
  m_model(1.0f),
  m_clearColor(0, 0, 0, 0),
  m_color(1, 1, 1, 1)
{ }

Renderer::~Renderer() { }

void Renderer::render()
{
  initialize();

  if(m_renderTexture)
  {
    ivec2 size = m_renderTexture->size();
    glViewport(0, 0, size.x, size.y);
    m_renderTexture->bind();
  }
  else
  {
    glViewport(0, 0, m_windowSize.x, m_windowSize.y);
  }

  glUseProgram(m_shader->id());

  if(m_blend)
  {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  if(m_backfaceCull)
  {
    glEnable(GL_CULL_FACE);
  }

  if(m_depthTest)
  {
    glEnable(GL_DEPTH_TEST);
  }

  if(m_texture)
  {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture->id());
    glUniform1i(m_shader->texture0Loc(), 0);
  }

  if(m_texture1)
  {
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, m_texture1->id());
    glUniform1i(m_shader->texture1Loc(), 1);
  }

  glUniform4f(m_shader->colorLoc(), m_color.x, m_color.y, m_color.z, m_color.w);

  glUniformMatrix4fv(m_shader->projectionLoc(), 1, GL_FALSE,
    glm::value_ptr(m_projection));

  glUniformMatrix4fv(m_shader->viewLoc(), 1, GL_FALSE,
    glm::value_ptr(m_view));

  if(m_mesh)
  {
    glUniformMatrix4fv(m_shader->modelLoc(), 1, GL_FALSE,
      glm::value_ptr(m_model));

    glBindVertexArray(m_mesh->id());
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_mesh->vertices());
    glBindVertexArray(0);
  }

  glUseProgram(0);

  if(m_texture1)
  {
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  if(m_texture)
  {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  if(m_backfaceCull)
  {
    glDisable(GL_CULL_FACE);
  }

  if(m_depthTest)
  {
    glDisable(GL_DEPTH_TEST);
  }

  if(m_blend)
  {
    glDisable(GL_BLEND);
  }

  if(m_renderTexture)
  {
    m_renderTexture->unbind();
  }
}

void Renderer::texture(sys::Ptr<Texture> _texture)
{
  m_texture = _texture;
}

void Renderer::texture1(sys::Ptr<Texture> _texture)
{
  m_texture1 = _texture;
}

void Renderer::color(const vec3& _color)
{
  m_color = vec4(_color, 1.0f);
}

void Renderer::color(const vec4& _color)
{
  m_color = _color;
}

sys::Ptr<Shader> Renderer::shader()
{
  return m_shader;
}

void Renderer::shader(sys::Ptr<Shader> _shader)
{
  m_shader = _shader;
}

sys::Ptr<Mesh> Renderer::mesh()
{
  return m_mesh;
}

void Renderer::mesh(sys::Ptr<Mesh> _mesh)
{
  m_mesh = _mesh;
}

mat4 Renderer::projection()
{
  return m_projection;
}

void Renderer::projection(const mat4& _projection)
{
  m_projection = _projection;
}

mat4 Renderer::view()
{
  return m_view;
}

void Renderer::view(const mat4& _view)
{
  m_view = _view;
}

mat4 Renderer::model()
{
  return m_model;
}

void Renderer::model(const mat4& _model)
{
  m_model = _model;
}

void Renderer::clearColor(const vec3& _clearColor)
{
  m_clearColor = vec4(_clearColor, 1);
}

void Renderer::backfaceCull(bool _backfaceCull)
{
  m_backfaceCull = _backfaceCull;
}

void Renderer::depthTest(bool _depthTest)
{
  m_depthTest = _depthTest;
}

void Renderer::blend(bool _blend)
{
  m_blend = _blend;
}

void Renderer::clear(bool _color)
{
  initialize();

  if(m_renderTexture)
  {
    m_renderTexture->bind();
  }

  glClearColor(
    m_clearColor.x,
    m_clearColor.y,
    m_clearColor.z,
    m_clearColor.w);

  if(!_color)
  {
    glClear(GL_DEPTH_BUFFER_BIT);
  }
  else
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  if(m_renderTexture)
  {
    m_renderTexture->unbind();
  }
}

Ray Renderer::raycast(int _x, int _y)
{
  Ray rtn;

  vec4 viewport;

  if(m_renderTexture)
  {
    viewport = vec4(0, 0, m_renderTexture->size().x, m_renderTexture->size().y);
  }
  else
  {
    viewport = vec4(0, 0, m_windowSize.x, m_windowSize.y);
  }

  _y = (int)viewport.w - _y;

  vec3 near = unProject(vec3(_x, _y, -1), m_view, m_projection, viewport);
  vec3 far = unProject(vec3(_x, _y, 1), m_view, m_projection, viewport);

  rtn.direction = normalize(far - near);
  //rtn.origin = inverse(m_view) * vec4(0, 0, 0, 1);
  rtn.origin = near;

  mat4 invModel = rend::inverse(m_model);
  rtn.origin = invModel * rend::vec4(rtn.origin, 1);
  rtn.direction = invModel * rend::vec4(rtn.direction, 0);

  return rtn;
}

void Renderer::initialize()
{
  static bool initialized = false;

  if(initialized)
  {
    return;
  }

  if(glewInit() != GLEW_OK)
  {
    sys::panic("Failed to initialize OpenGL");
  }

  initialized = true;
}

}

