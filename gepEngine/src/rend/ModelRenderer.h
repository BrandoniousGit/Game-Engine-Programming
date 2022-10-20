#include "rendmath.h"
#include "Renderer.h"

#include "sys/Ptr.h"

namespace rend
{

struct RenderTexture;
struct Model;
struct Animation;
struct Ray;
struct Part;

struct ModelRenderer : Renderer
{
  ModelRenderer(int _width, int _height);
  ModelRenderer(sys::Ptr<RenderTexture> _renderTexture);

  void model(sys::Ptr<Model> _model);
  void animation(sys::Ptr<Animation> _animation);
  void frame(float _frame);

  sys::Ptr<Part> intersect(const Ray& _ray, float& _distance) const;

  void render();

private:
  sys::Ptr<Model> m_modelPtr;
  sys::Ptr<Animation> m_animation;
  sys::Zero<float> m_frame;

};

}
