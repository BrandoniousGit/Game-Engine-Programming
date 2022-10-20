#ifndef SYS_STRING_H
#define SYS_STRING_H

#include "Vector.h"
#include "Ptr.h"
#include "panic.h"

#include <string.h>

#define SYS_TAKE_RAW                 \
  size_t len = strlen(_value);       \
  m_data.resize(len + 1);            \
                                     \
  for(size_t ci = 0; ci < len; ++ci) \
  {                                  \
    m_data[ci] = _value[ci];         \
  }                                  \
                                     \
  m_data[m_data.size() - 1] = 0;     \

namespace sys
{

struct String : EnablePtr
{
  String()
  {
    m_data.push(0);
  }

  String(const char* _value)
  {
    SYS_TAKE_RAW
  }

  String& operator=(const char* _value)
  {
    SYS_TAKE_RAW

    return *this;
  }

  String& operator+=(const String& _value)
  {
    size_t len = _value.length();
    size_t cs = length();

    m_data.resize(cs + len + 1);

    for(size_t ci = 0; ci < len; ++ci)
    {
      m_data[cs + ci] = _value[ci];
    }

    m_data[m_data.size() - 1] = 0;

    return *this;
  }

  String& operator+=(char _value)
  {
    m_data[m_data.size() - 1] = _value;
    m_data.push(0);

    return *this;
  }

  String& operator+=(const char* _value)
  {
    size_t len = strlen(_value);
    size_t cs = length();

    m_data.resize(cs + len + 1);

    for(size_t ci = 0; ci < len; ++ci)
    {
      m_data[cs + ci] = _value[ci];
    }

    m_data[m_data.size() - 1] = 0;

    return *this;
  }

  bool operator==(const String& _other) const
  {
    if(strcmp(m_data.unsafe_raw(), _other.m_data.unsafe_raw()) == 0)
    {
      return true;
    }

    return false;
  }

  bool operator!=(const String& _other) const
  {
    if(strcmp(m_data.unsafe_raw(), _other.m_data.unsafe_raw()) != 0)
    {
      return true;
    }

    return false;
  }

  bool operator<(const String& _other) const
  {
    if(strcmp(m_data.unsafe_raw(), _other.m_data.unsafe_raw()) < 0)
    {
      return true;
    }

    return false;
  }

  bool operator>(const String& _other) const
  {
    if(strcmp(m_data.unsafe_raw(), _other.m_data.unsafe_raw()) > 0)
    {
      return true;
    }

    return false;
  }

  bool operator<=(const String& _other) const
  {
    if(strcmp(m_data.unsafe_raw(), _other.m_data.unsafe_raw()) <= 0)
    {
      return true;
    }

    return false;
  }

  bool operator>=(const String& _other) const
  {
    if(strcmp(m_data.unsafe_raw(), _other.m_data.unsafe_raw()) >= 0)
    {
      return true;
    }

    return false;
  }

  char& operator[](const IndexLock& _index)
  {
    if(_index >= length())
    {
      printf("Character index out of bounds %i, %i", (int)_index, (int)length());
      panic("Character index out of bounds");
    }

    return m_data[_index];
  }

  const char& operator[](const IndexLock& _index) const
  {
    if(_index >= length())
    {
      panic("Character (const) index out of bounds");
    }

    return m_data[_index];
  }

  size_t length() const
  {
    return m_data.size() - 1;
  }

  void resize(size_t _newSize)
  {
    m_data.resize(_newSize + 1);
    m_data[_newSize] = 0;
  }

  void clear()
  {
    m_data.resize(1);
    m_data[0] = 0;
  }

  const char* unsafe_raw() const
  {
    return m_data.unsafe_raw();
  }

  String substring(size_t _begin, size_t _count) const
  {
    if(_begin + _count > length())
    {
      sys::panic("Substring out of bounds");
    }

    String rtn;

    for(size_t i = _begin; i < _begin + _count; ++i)
    {
      rtn += m_data[i];
    }

    return rtn;
  }

  String substring(size_t _begin) const
  {
    if(_begin > length())
    {
      sys::panic("Substring begins out of bounds");
    }

    return substring(_begin, length() - _begin);
  }

private:
  Vector<char> m_data;

};

}

#endif

