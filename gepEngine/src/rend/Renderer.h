#ifndef REND_RENDERER_H
#define REND_RENDERER_H

#include "rendmath.h"

#include "sys/Zero.h"
#include "sys/Ptr.h"

namespace rend
{

struct Shader;
struct Mesh;
struct Texture;
struct RenderTexture;

struct Renderer : sys::EnablePtr
{
  Renderer(int _width, int _height);
  Renderer(sys::Ptr<RenderTexture> _renderTexture);
  virtual ~Renderer();

  virtual void render();

  sys::Ptr<Shader> shader();
  void shader(sys::Ptr<Shader> _shader);

  sys::Ptr<Mesh> mesh();
  void mesh(sys::Ptr<Mesh> _mesh);

  void texture(sys::Ptr<Texture> _texture);
  void texture1(sys::Ptr<Texture> _texture);
  void color(const vec3& _color);
  void color(const vec4& _color);

  mat4 projection();
  void projection(const mat4& _projection);

  mat4 model();
  void model(const mat4& _model);

  mat4 view();
  void view(const mat4& _view);

  void backfaceCull(bool _backfaceCull);
  void depthTest(bool _depthTest);

  void clearColor(const vec3& _clearColor);
  void clear(bool _color = true);

  void blend(bool _blend);

  Ray raycast(int _x, int _y);

protected:
  sys::Ptr<RenderTexture> m_renderTexture;
  sys::Ptr<Shader> m_shader;
  sys::Ptr<Mesh> m_mesh;
  sys::Ptr<Texture> m_texture;
  sys::Ptr<Texture> m_texture1;
  mat4 m_projection;
  mat4 m_view;
  mat4 m_model;
  sys::Zero<bool> m_depthTest;
  sys::Zero<bool> m_backfaceCull;
  sys::Zero<bool> m_blend;
  vec4 m_clearColor;
  vec4 m_color;
  ivec2 m_windowSize;

  static void initialize();
};

}

#endif

