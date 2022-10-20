#ifndef SYS_FILE_H
#define SYS_FILE_H

#include "Zero.h"
#include "String.h"
#include "Exception.h"
#include "panic.h"
#include "Vector.h"

#include <stdio.h>

namespace sys
{

struct File
{
  File(const String& _path) : m_path(_path) { }

  ~File()
  {
    if(m_raw)
    {
      fclose(m_raw);
    }
  }

  size_t read(Vector<unsigned char>& _output)
  {
    if(m_mode != 1)
    {
      openRead();
    }

    return fread(_output.unsafe_raw(), sizeof(_output[0]), _output.size(), m_raw);
  }

  void write_line(const String& _line)
  {
    if(m_mode != 2)
    {
      openWrite();
    }

    if(fputs(_line.unsafe_raw(), m_raw) < 0)
    {
      throw Exception("Failed to write");
    }

    if(fputs("\n", m_raw) < 0)
    {
      throw Exception("Failed to write EOL");
    }
  }

  bool read_line(String& _line)
  {
    static char buffer[2048] = { 0 };

    if(m_mode != 1)
    {
      openRead();
    }

    _line.clear();

    while(true)
    {
      char *res = fgets(buffer, sizeof(buffer), m_raw);
      if(!res) break;
      _line += res;
      if(_line.length() < 1) sys::panic("Invalid read");

      if(strip_endl(_line))
      {
        // New line char was encountered, end of line reached
        return true;
      }
    }

    if(_line.length() > 0)
    {
      // End of file reached, data remained
      strip_endl(_line);
      return true;
    }

    // End of file reached, no data
    return false;
  }

private:
  String m_path;
  Zero<int> m_mode;
  Zero<FILE *> m_raw;

  File(const File& _copy);
  File& operator=(const File& _other);

  void openRead()
  {
    if(m_raw)
    {
      fclose(m_raw);
    }

    m_mode = 0;
#ifdef _MSC_VER
    if(fopen_s(&m_raw, m_path.unsafe_raw(), "rb"))
    {
      throw Exception("Failed to open file for reading");
    }
#else
    m_raw = fopen(m_path.unsafe_raw(), "rb");
    if(!m_raw) throw Exception("Failed to open file for reading");
#endif

    m_mode = 1;
  }

  void openWrite()
  {
    if(m_raw)
    {
      fclose(m_raw);
    }

    m_mode = 0;
#ifdef _MSC_VER
    if(fopen_s(&m_raw, m_path.unsafe_raw(), "wb"))
    {
      throw Exception("Failed to open file for writing");
    }
#else
    m_raw = fopen(m_path.unsafe_raw(), "wb");
    if(!m_raw) throw Exception("Failed to open file for writing");
#endif
    m_mode = 2;
  }

  bool strip_endl(String& _str)
  {
    ssize_t cleanLen = -1;
    bool found = false;

    for(ssize_t ci = _str.length() - 1; ci >= 0; --ci)
    {
      char c = _str[ci];

      if(c != '\n' && c != '\r')
      {
        break;
      }

      if(c == '\n')
      {
        found = true;
      }

      cleanLen = ci;
    }

    if(cleanLen != -1)
    {
      _str.resize(cleanLen);
    }

    return found;
  }

};

}

#endif

