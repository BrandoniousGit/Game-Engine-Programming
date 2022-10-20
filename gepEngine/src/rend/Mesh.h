#ifndef REND_MESH_H
#define REND_MESH_H

#include "rendmath.h"

#include <GL/glew.h>

#include "sys/List.h"
#include "sys/Zero.h"
#include "sys/Vector.h"
#include "sys/String.h"

namespace rend
{

struct Buffer;

struct Vertex
{
  vec3 position;
  vec2 texcoord;
  vec3 normal;
};

struct Face
{
  Vertex a;
  Vertex b;
  Vertex c;

  bool hasTexCoords() const;
  bool hasNormals() const;
  vec3 calculateNormal() const;
};

struct Mesh : sys::EnablePtr
{
  Mesh();
  Mesh(const sys::String& _path);
  ~Mesh();

  void add(const Face& _face);
  GLuint id();
  size_t vertices();
  void load(const sys::String& _path);
  void loadTriangle();
  void loadQuad();
  void loadGuiQuad();
  void loadNdcQuad();

  bool intersect(const Ray& _ray) const;
  bool intersect(const Ray& _ray, float& _distance) const;
  sys::Ptr<sys::Vector<Face> > faces();

private:
  sys::Zero<bool> m_dirty;
  sys::List<Buffer> m_buffers;
  sys::Zero<GLuint> m_id;
  sys::Vector<Triangle> m_triangles;
  sys::Vector<Face> m_faces;

  sys::Ptr<Buffer> m_positions;
  sys::Ptr<Buffer> m_texcoords;
  sys::Ptr<Buffer> m_normals;

  Mesh(const Mesh& _copy);
  Mesh& operator=(const Mesh& _other);
};

}

#endif

