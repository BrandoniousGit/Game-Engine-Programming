#include "Mesh.h"
#include "Buffer.h"
#include "rendmath.h"

#include "sys/File.h"
#include "sys/Vector.h"
#include "sys/Exception.h"

namespace rend
{

Mesh::Mesh() :
  m_dirty(true)
{ }

/*
Mesh::Mesh(const Mesh& _copy) :
  m_dirty(true),
  m_buffers(_copy.m_buffers)
{ }
*/

Mesh::~Mesh()
{
  if(m_id)
  {
    glDeleteVertexArrays(1, &m_id);
  }
}

Mesh::Mesh(const sys::String& _path)
{
   load(_path);
}

void Mesh::add(const Face& _face)
{
  m_faces.push(_face);

  m_dirty = true;
}

size_t Mesh::vertices()
{
  sys::List<Buffer>::Iterator first = m_buffers.begin();

  if(first == m_buffers.end())
  {
    return 0;
  }

  return first->size() / first->components();
}

GLuint Mesh::id()
{
  if(!m_id)
  {
    glGenVertexArrays(1, &m_id);
    if(!m_id) throw sys::Exception("Failed to create vertex array");
  }

  if(m_dirty)
  {
    if(m_positions) m_positions->clear();
    if(m_texcoords) m_texcoords->clear();
    if(m_normals) m_normals->clear();

    for(sys::Vector<Face>::Iterator fit = m_faces.begin();
      fit != m_faces.end(); ++fit)
    {
      if(!m_positions) m_positions = m_buffers.emplace();
      m_positions->add(fit->a.position);
      m_positions->add(fit->b.position);
      m_positions->add(fit->c.position);

      if(fit->hasTexCoords())
      {
        if(!m_texcoords) m_texcoords = m_buffers.emplace();
        m_texcoords->add(fit->a.texcoord);
        m_texcoords->add(fit->b.texcoord);
        m_texcoords->add(fit->c.texcoord);
      }

      if(!m_normals) m_normals = m_buffers.emplace();

      if(!fit->hasNormals())
      {
        vec3 normal = fit->calculateNormal();
        m_normals->add(normal);
        m_normals->add(normal);
        m_normals->add(normal);
      }
      else
      {
        m_normals->add(fit->a.normal);
        m_normals->add(fit->b.normal);
        m_normals->add(fit->c.normal);
      }
    }

    GLuint i = 0;

    glBindVertexArray(m_id);

    for(sys::List<Buffer>::Iterator it = m_buffers.begin();
      it != m_buffers.end(); ++it)
    {
      glBindBuffer(GL_ARRAY_BUFFER, it->id());
      glVertexAttribPointer(i, it->components(), GL_FLOAT, GL_FALSE, 0, (void*)0);
      glEnableVertexAttribArray(i);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      ++i;
    }

    glBindVertexArray(0);
    m_dirty = false;
  }

  return m_id;
}

static void split_string_whitespace(const sys::String& _input,
  sys::Vector<sys::String> _output)
{
  _output.clear();
  sys::String curr;

  for(size_t ci = 0; ci < _input.length(); ++ci)
  {
    char c = _input[ci];

    if(c == '\r' || c == '\n' || c == ' ' || c == '\t')
    {
      if(curr.length() > 0)
      {
        _output.push(curr);
        curr = "";
      }
    }
    else
    {
      curr += c;
    }
  }

  if(curr.length() > 0)
  {
    _output.push(curr);
  }
}

static void split_string(const sys::String& _input, char splitter,
  sys::Vector<sys::String> _output)
{
  _output.clear();
  sys::String curr;

  for(size_t ci = 0; ci < _input.length(); ++ci)
  {
    char c = _input[ci];

    if(c == splitter)
    {
      _output.push(curr);
      curr = "";
    }
    else
    {
      curr += c;
    }
  }

  if(curr.length() > 0)
  {
    _output.push(curr);
  }
}

void Mesh::loadTriangle()
{
  if(m_buffers.begin() != m_buffers.end())
  {
    sys::panic("Buffers already loaded");
  }

  Face f;
  f.a.position = vec3(0.0f, 0.5f, 0);
  f.b.position = vec3(-0.5f, -0.5f, 0);
  f.c.position = vec3(0.5f, -0.5f, 0);
  f.a.texcoord = vec2(0.5f, 1.0f);
  f.b.texcoord = vec2(0.0f, 0.0f);
  f.c.texcoord = vec2(1.0f, 0.0f);
  f.a.normal = vec3(0, 0, 1);
  f.b.normal = vec3(0, 0, 1);
  f.c.normal = vec3(0, 0, 1);
  add(f);
}

void Mesh::loadNdcQuad()
{
  if(m_buffers.begin() != m_buffers.end())
  {
    sys::panic("Buffers already loaded");
  }

  Face f;
  f.a.position = vec3(-1.0f, 1.0f, 0);
  f.b.position = vec3(-1.0f, -1.0f, 0);
  f.c.position = vec3(1.0f, -1.0f, 0);
  add(f);
  f.a.position = vec3(1.0f, -1.0f, 0);
  f.b.position = vec3(1.0f, 1.0f, 0);
  f.c.position = vec3(-1.0f, 1.0f, 0);
  add(f);
}

void Mesh::loadQuad()
{
  if(m_buffers.begin() != m_buffers.end())
  {
    sys::panic("Buffers already loaded");
  }

  Face f;
  f.a.position = vec3(-0.5f, 0.5f, 0);
  f.b.position = vec3(-0.5f, -0.5f, 0);
  f.c.position = vec3(0.5f, -0.5f, 0);
  f.a.texcoord = vec2(0.0f, 1.0f);
  f.b.texcoord = vec2(0.0f, 0.0f);
  f.c.texcoord = vec2(1.0f, 0.0f);
  f.a.normal = vec3(0, 0, 1);
  f.b.normal = vec3(0, 0, 1);
  f.c.normal = vec3(0, 0, 1);
  add(f);

  f.a.position = vec3(0.5f, -0.5f, 0);
  f.b.position = vec3(0.5f, 0.5f, 0);
  f.c.position = vec3(-0.5f, 0.5f, 0);
  f.a.texcoord = vec2(1.0f, 0.0f);
  f.b.texcoord = vec2(1.0f, 1.0f);
  f.c.texcoord = vec2(0.0f, 1.0f);
  f.a.normal = vec3(0, 0, 1);
  f.b.normal = vec3(0, 0, 1);
  f.c.normal = vec3(0, 0, 1);
  add(f);
}

void Mesh::loadGuiQuad()
{
  if(m_buffers.begin() != m_buffers.end())
  {
    sys::panic("Buffers already loaded");
  }

  Face f;
  f.a.position = vec3(0.0f, 0.0f, 0);
  f.b.position = vec3(0.0f, 1.0f, 0);
  f.c.position = vec3(1.0f, 1.0f, 0);
  f.a.texcoord = vec2(0.0f, 1.0f);
  f.b.texcoord = vec2(0.0f, 0.0f);
  f.c.texcoord = vec2(1.0f, 0.0f);
  f.a.normal = vec3(0, 0, 1);
  f.b.normal = vec3(0, 0, 1);
  f.c.normal = vec3(0, 0, 1);
  add(f);

  f.a.position = vec3(1.0f, 1.0f, 0);
  f.b.position = vec3(1.0f, 0.0f, 0);
  f.c.position = vec3(0.0f, 0.0f, 0);
  f.a.texcoord = vec2(1.0f, 0.0f);
  f.b.texcoord = vec2(1.0f, 1.0f);
  f.c.texcoord = vec2(0.0f, 1.0f);
  f.a.normal = vec3(0, 0, 1);
  f.b.normal = vec3(0, 0, 1);
  f.c.normal = vec3(0, 0, 1);
  add(f);
}

void Mesh::load(const sys::String& _path)
{
  if(m_buffers.begin() != m_buffers.end())
  {
    sys::panic("Buffers already loaded");
  }

  sys::String line;
  sys::Vector<sys::String> tokens;
  sys::Vector<vec3> positions;
  sys::Vector<vec2> texcoords;
  sys::Vector<vec3> normals;
  sys::Vector<sys::String> innerTokens;

  for(sys::File file(_path); file.read_line(line);)
  {
    if(line.length() < 1) continue;

    split_string_whitespace(line, tokens);

    if(tokens[0] == "v" && tokens.size() >= 4)
    {
      vec3 p(
        atof(tokens[1].unsafe_raw()),
        atof(tokens[2].unsafe_raw()),
        atof(tokens[3].unsafe_raw()));

      positions.push(p);
    }
    else if(tokens[0] == "vt" && tokens.size() >= 3)
    {
      vec2 p(
        atof(tokens[1].unsafe_raw()),
        atof(tokens[2].unsafe_raw()));

      texcoords.push(p);
    }
    else if(tokens[0] == "vn" && tokens.size() >= 4)
    {
      vec3 n(
        atof(tokens[1].unsafe_raw()),
        atof(tokens[2].unsafe_raw()),
        atof(tokens[3].unsafe_raw()));

      normals.push(n);
    }
    else if(tokens[0] == "f" && tokens.size() >= 4)
    {
      split_string(tokens[1], '/', innerTokens);
      int pa = atoi(innerTokens[0].unsafe_raw()) - 1;
      int tca = atoi(innerTokens[1].unsafe_raw()) - 1;
      int na = atoi(innerTokens[2].unsafe_raw()) - 1;
      split_string(tokens[2], '/', innerTokens);
      int pb = atoi(innerTokens[0].unsafe_raw()) - 1;
      int tcb = atoi(innerTokens[1].unsafe_raw()) - 1;
      int nb = atoi(innerTokens[2].unsafe_raw()) - 1;
      split_string(tokens[3], '/', innerTokens);
      int pc = atoi(innerTokens[0].unsafe_raw()) - 1;
      int tcc = atoi(innerTokens[1].unsafe_raw()) - 1;
      int nc = atoi(innerTokens[2].unsafe_raw()) - 1;

      Face f;
      f.a.position = positions[pa];
      f.b.position = positions[pb];
      f.c.position = positions[pc];
      f.a.texcoord = texcoords[tca];
      f.b.texcoord = texcoords[tcb];
      f.c.texcoord = texcoords[tcc];
      f.a.normal = normals[na];
      f.b.normal = normals[nb];
      f.c.normal = normals[nc];
      add(f);

      Triangle t;
      t.a = f.a.position;
      t.b = f.b.position;
      t.c = f.c.position;
      m_triangles.push(t);

      if(tokens.size() >= 5)
      {
        f.b = f.a;
        f.a = f.c;
        f.c = f.b;

        split_string(tokens[4], '/', innerTokens);
        f.b.position = positions[atoi(innerTokens[0].unsafe_raw()) - 1];
        f.b.texcoord = texcoords[atoi(innerTokens[1].unsafe_raw()) - 1];
        f.b.normal = normals[atoi(innerTokens[2].unsafe_raw()) - 1];
        add(f);

        t.a = f.a.position;
        t.b = f.b.position;
        t.c = f.c.position;
        m_triangles.push(t);
      }
    }
  }
}

bool Mesh::intersect(const Ray& _ray, float& _distance) const
{
  bool rtn = false;
  _distance = FLT_MAX;

  for(size_t fi = 0; fi < m_faces.size(); ++fi)
  {
    Face f = m_faces[fi];
    vec2 bary;
    float nd = 0;

    if(intersectRayTriangle(_ray.origin, _ray.direction,
      f.a.position, f.b.position, f.c.position, bary, nd) == true)
    {
      rtn = true;

      if(nd < _distance)
      {
        _distance = nd;
      }
    }
  }

  return rtn;
}

bool Mesh::intersect(const Ray& _ray) const
{
  for(size_t fi = 0; fi < m_faces.size(); ++fi)
  {
    Face f = m_faces[fi];
    vec2 bary;
    float distance = 0;

    if(intersectRayTriangle(_ray.origin, _ray.direction,
      f.a.position, f.b.position, f.c.position, bary, distance) == true)
    {
      return true;
    }
  }

  return false;
}

sys::Ptr<sys::Vector<Face> > Mesh::faces()
{
  return &m_faces;
}

bool Face::hasTexCoords() const
{
  vec2 val;
  val += a.texcoord;
  val += b.texcoord;
  val += c.texcoord;

  if(val.x + val.y == 0) return false;

  return true;
}

bool Face::hasNormals() const
{
  vec3 val;
  val += a.normal;
  val += b.normal;
  val += c.normal;

  if(val.x + val.y + val.z == 0) return false;

  return true;
}

vec3 Face::calculateNormal() const
{
  vec3 u = b.position - a.position;
  vec3 v = c.position - a.position;

  vec3 rtn;
  rtn.x = u.y * v.z - u.z * v.y;
  rtn.y = u.z * v.x - u.x * v.z;
  rtn.z = u.x * v.y - u.y * v.x;

  return rtn;
}

}

