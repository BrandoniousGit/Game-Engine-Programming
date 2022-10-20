#ifndef SYS_PIPE_H
#define SYS_PIPE_H

#include "Zero.h"
#include "String.h"
#include "Exception.h"
#include "panic.h"
#include "Vector.h"

#include <stdio.h>

namespace sys
{

struct Pipe
{
  Pipe(const String& _command)
  {
    if(!open(_command))
    {
      throw Exception("Failed to open pipe");
    }
  }

  ~Pipe()
  {
    if(m_raw)
    {
      pclose(m_raw);
    }
  }

  bool open(const String& _command)
  {
    if(m_raw)
    {
      pclose(m_raw);
    }

    m_raw = popen(_command.unsafe_raw(), "r");
    if(!m_raw) return false;

    return true;
  }

  size_t read(Vector<unsigned char>& _output)
  {
    return fread(_output.unsafe_raw(), sizeof(_output[0]), _output.size(), m_raw);
  }

  bool read_line(String& _line)
  {
    static char buffer[2048] = { 0 };

    if(!m_raw) panic("Pipe not open for reading");
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
  Zero<FILE *> m_raw;

  Pipe(const Pipe& _copy);
  Pipe& operator=(const Pipe& _other);

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

