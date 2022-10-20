#ifndef SYS_MUTEX_H
#define SYS_MUTEX_H

#include "panic.h"

#include <pthread.h>

namespace sys
{

struct Mutex
{
  Mutex()
  {
    if(pthread_mutex_init(&m_lock, NULL))
    {
      panic("Failed to initialize mutex");
    }
  }

  ~Mutex()
  {
    if(pthread_mutex_destroy(&m_lock))
    {
      panic("Failed to destroy mutex");
    }
  }

  void lock() const
  {
    pthread_mutex_lock(&m_lock);
  }

  void unlock() const
  {
    pthread_mutex_unlock(&m_lock);
  }

private:
  mutable pthread_mutex_t m_lock;

  Mutex(const Mutex& _copy);
  Mutex& operator=(const Mutex& _other);
};

}

#endif

