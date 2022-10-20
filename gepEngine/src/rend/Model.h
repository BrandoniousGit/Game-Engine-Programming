#include "Mesh.h"
#include "Texture.h"
#include "rendmath.h"

#include "sys/Ptr.h"
#include "sys/List.h"
#include "sys/String.h"
#include "sys/Vector.h"
#include "sys/Zero.h"

struct Texture;

namespace rend
{

struct MaterialGroup : sys::EnablePtr
{
  Mesh mesh;
  sys::Ptr<Texture> texture;
};

struct Part : sys::EnablePtr
{
  sys::String name;
  sys::List<MaterialGroup> mgs;
  vec3 offset;
  vec4 color;
};

struct Model : sys::EnablePtr
{
  Model(const sys::String& _path);

  sys::List<Part>::Iterator partsBegin();
  sys::List<Part>::Iterator partsEnd();

  bool intersect(const Ray& _ray) const;
  sys::Ptr<Part> intersect(const Ray& _ray, float& _distance) const;
  void color(vec4 _color);

private:
  sys::List<Texture> m_textures;
  sys::List<Part> m_parts;
  sys::Vector<Face> m_faces;

  void load(const sys::String& _path);
  void center_parts();
};

}

