#include "ModelRenderer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "Model.h"
#include "Animation.h"

#include "sys/Exception.h"

namespace rend
{

ModelRenderer::ModelRenderer(int _width, int _height) :
  Renderer(_width, _height)
{ }

ModelRenderer::ModelRenderer(sys::Ptr<RenderTexture> _renderTexture) :
  Renderer(_renderTexture)
{ }

void ModelRenderer::render()
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

  glUniformMatrix4fv(m_shader->projectionLoc(), 1, GL_FALSE,
    glm::value_ptr(m_projection));

  glUniformMatrix4fv(m_shader->viewLoc(), 1, GL_FALSE,
    glm::value_ptr(m_view));

  if(m_modelPtr)
  {
    for(sys::List<Part>::Iterator pit = m_modelPtr->partsBegin();
      pit != m_modelPtr->partsEnd(); ++pit)
    {
      vec4 color(m_color * pit->color);
      glUniform4f(m_shader->colorLoc(), color.x, color.y, color.z, color.w);

      mat4 model(m_model);

      if(m_animation)
      {
        model = model * m_animation->model(*pit, 0);
      }

      glUniformMatrix4fv(m_shader->modelLoc(), 1, GL_FALSE,
        glm::value_ptr(model));

      for(sys::List<MaterialGroup>::Iterator mit = pit->mgs.begin();
        mit != pit->mgs.end(); ++mit)
      {
        glBindVertexArray(mit->mesh.id());
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)mit->mesh.vertices());
      }
    }
  }

  glBindVertexArray(0);
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

void ModelRenderer::model(sys::Ptr<Model> _model)
{
  m_modelPtr = _model;
}

void ModelRenderer::animation(sys::Ptr<Animation> _animation)
{
  m_animation = _animation;
}

void ModelRenderer::frame(float _frame)
{
  m_frame = _frame;
}

sys::Ptr<Part> ModelRenderer::intersect(const Ray& _ray, float& _distance) const
{
  sys::Ptr<Part> rtn;

  _distance = FLT_MAX;
  if(!m_modelPtr) return NULL;

  for(sys::List<Part>::Iterator pit = m_modelPtr->partsBegin();
    pit != m_modelPtr->partsEnd(); ++pit)
  {
    Ray r(_ray);
    mat4 invModel(m_model);

    if(m_animation)
    {
      invModel = invModel * m_animation->model(*pit, m_frame);
    }

    invModel = inverse(invModel);

    r.origin = invModel *
      rend::vec4(r.origin, 1);

    r.direction = invModel *
      rend::vec4(r.direction, 0);

    for(sys::List<MaterialGroup>::Iterator mit = pit->mgs.begin();
      mit != pit->mgs.end(); ++mit)
    {
      float nd = FLT_MAX;

      if(mit->mesh.intersect(r, nd))
      {
        if(nd < _distance)
        {
          { Part& p(*pit); rtn = &p; }
          _distance = nd;
        }
      }
    }
  }

  return rtn;
}

}

