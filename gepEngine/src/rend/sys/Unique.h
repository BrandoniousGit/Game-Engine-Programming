#ifndef SYS_UNIQUE_H
#define SYS_UNIQUE_H

#include "panic.h"
#include "Zero.h"
#include "Lock.h"
#include "config.h"

namespace sys
{

template <typename T>
struct Ptr;

template <typename T>
struct Unique;

template <typename T>
struct Unique
{
  static Unique<T> make();

  Unique();
  Unique(const Unique& _copy);
  Unique& operator=(const Unique& _other);
  ~Unique();

  template <typename U> Unique(const Unique<U>& _other);
  template <typename U> Unique& operator=(const Unique<U>& _other);

#ifdef SYS_DEBUG
  RefLock<T> operator*() const;
  PtrLock<T> operator->() const;
  PtrLock<T> get() const;
#else
  T& operator*() const;
  T* operator->() const;
  T* get() const;
#endif

  void reset();

  template <typename U> bool operator==(const Unique<U>& _other) const;
  template <typename U> bool operator!=(const Unique<U>& _other) const;

private:
  template <typename U>
  friend struct Ptr;

  template <typename U>
  friend struct Unique;

  mutable Zero<T*> m_ptr;
  mutable Zero<void (*)(void*)> m_deleter;
  mutable Zero<LockBlock*> m_lock;

  static void deleter(void* _ptr);
};

}

/* Implementation */

namespace sys
{

template <typename T>
Unique<T> Unique<T>::make()
{
  Unique<T> rtn;

  rtn.m_ptr = new T();
  rtn.m_deleter = deleter;

#ifdef SYS_DEBUG
  rtn.m_lock = new LockBlock();
  rtn.m_lock->type_name = typeid(T).name();
#endif

  return rtn;
}

template <typename T>
Unique<T>::Unique()
{ }

template <typename T>
Unique<T>::Unique(const Unique& _copy) :
  m_ptr(_copy.m_ptr),
  m_deleter(_copy.m_deleter),
  m_lock(_copy.m_lock)
{
  _copy.m_ptr = NULL;
  _copy.m_deleter = NULL;
  _copy.m_lock = NULL;
}

template <typename T>
Unique<T>& Unique<T>::operator=(const Unique& _other)
{
  if(m_ptr != _other.m_ptr ||
    m_deleter != _other.m_deleter ||
    m_lock != _other.m_lock)
  {
    reset();

    m_ptr = _other.m_ptr;
    _other.m_ptr = NULL;

    m_deleter = _other.m_deleter;
    _other.m_deleter = NULL;

    m_lock = _other.m_lock;
    _other.m_lock = NULL;
  }

  return *this;
}

template <typename T>
void Unique<T>::reset()
{
  if(!m_ptr) return;

  void (*deleter)(void*) = m_deleter;
  deleter(m_ptr);

#ifdef SYS_DEBUG
  if(m_lock)
  {
    printf("Destructing %s\n", (const char*)m_lock->type_name);
  }

  LockBlock* lock = m_lock;
  delete lock;
#endif
}

template <typename T>
Unique<T>::~Unique()
{
  reset();
}

template <typename T>
template <typename U>
Unique<T>::Unique(const Unique<U>& _other) :
  m_ptr(_other.m_ptr),
  m_deleter(_other.m_deleter),
  m_lock(_other.m_lock)
{
  _other.m_ptr = NULL;
  _other.m_deleter = NULL;
  _other.m_lock = NULL;
}

template <typename T>
template <typename U>
Unique<T>& Unique<T>::operator=(const Unique<U>& _other)
{
  if(m_ptr != _other.m_ptr ||
    m_deleter != _other.m_deleter ||
    m_lock != _other.m_lock)
  {
    reset();

    m_ptr = _other.m_ptr;
    _other.m_ptr = NULL;

    m_deleter = _other.m_deleter;
    _other.m_deleter = NULL;

    m_lock = _other.m_lock;
    _other.m_lock = NULL;
  }

  return *this;
}

#ifdef SYS_DEBUG
template <typename T>
RefLock<T> Unique<T>::operator*() const
{
  if(!m_ptr)
  {
    sys::panic("Attempt to dereference NULL pointer");
  }

  return RefLock<T>(m_ptr, m_lock);
}

template <typename T>
PtrLock<T> Unique<T>::operator->() const
{
  if(!m_ptr)
  {
    sys::panic("Attempt to dereference NULL pointer");
  }

  return PtrLock<T>(m_ptr, m_lock);
}

template <typename T>
PtrLock<T> Unique<T>::get() const
{
  if(!m_ptr)
  {
    sys::panic("Attempt to dereference NULL pointer");
  }

  return PtrLock<T>(m_ptr, m_lock);
}

#else
template <typename T>
T& Unique<T>::operator*() const
{
  return *m_ptr;
}

template <typename T>
T* Unique<T>::operator->() const
{
  return m_ptr;
}

template <typename T>
T* Unique<T>::get() const
{
  return m_ptr;
}
#endif

template <typename T>
void Unique<T>::deleter(void* _ptr)
{
  T* ptr = static_cast<T*>(_ptr);
  delete ptr;
}

template <typename T>
template <typename U>
bool Unique<T>::operator==(const Unique<U>& _other) const
{
  return m_ptr == _other.m_ptr;
}

template <typename T>
template <typename U>
bool Unique<T>::operator!=(const Unique<U>& _other) const
{
  return m_ptr != _other.m_ptr;
}

}

#endif

