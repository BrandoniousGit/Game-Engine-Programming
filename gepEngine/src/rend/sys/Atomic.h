#ifndef SYS_ATOMIC_H
#define SYS_ATOMIC_H

#include "Zero.h"
#include "panic.h"

#include <pthread.h>

namespace sys
{

template <typename T>
struct Atomic
{
  Atomic();
  ~Atomic();

  operator T() const;

  Atomic& operator++();
  Atomic& operator--();

private:
  Zero<T> m_value;
  mutable pthread_mutex_t m_lock;
  Zero<bool> m_active;

  Atomic(const Atomic& _copy);
  Atomic& operator=(const Atomic& _other);
};

template <typename T>
Atomic<T>::Atomic()
{
  if(pthread_mutex_init(&m_lock, NULL))
  {
    panic("Failed to initialize mutex");
  }
}

template <typename T>
Atomic<T>::~Atomic()
{
  if(pthread_mutex_destroy(&m_lock))
  {
    panic("Failed to destroy mutex");
  }
}

template <typename T>
Atomic<T>::operator T() const
{
  if(m_active) pthread_mutex_lock(&m_lock);
  T rtn = m_value;
  if(m_active) pthread_mutex_unlock(&m_lock);

  return rtn;
}

template <typename T>
Atomic<T>& Atomic<T>::operator++()
{
  if(m_active) pthread_mutex_lock(&m_lock);
  ++m_value;
  if(m_active) pthread_mutex_unlock(&m_lock);

  return *this;
}

template <typename T>
Atomic<T>& Atomic<T>::operator--()
{
  if(m_active) pthread_mutex_lock(&m_lock);
  --m_value;
  if(m_active) pthread_mutex_unlock(&m_lock);

  return *this;
}

}

#endif

