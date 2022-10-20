#ifndef SYS_EXCEPTION_H
#define SYS_EXCEPTION_H

#include "String.h"
#include "Ptr.h"
#include "panic.h"

namespace sys
{

struct Exception
{
  //Exception() { }

  Exception(const String& _message) :
    m_message(_message)
  {
    printf("%s\n", _message.unsafe_raw());
  }

  virtual ~Exception() { }

  Ptr<const String> what() const
  {
    return &m_message;
  }

  void panic() const
  {
    sys::panic(m_message.unsafe_raw());
  }

private:
  String m_message;
};

}

#endif

