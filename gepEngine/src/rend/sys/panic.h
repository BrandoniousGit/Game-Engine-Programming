#ifndef SYS_PANIC_H
#define SYS_PANIC_H

#include <stdio.h>
#include <stdlib.h>

namespace sys
{

template <typename T>
void panic(T _message, T _unused = "")
{
  const char* message = _message;
  printf("Panic: %s\n", message);
  abort();
}

}

#endif

