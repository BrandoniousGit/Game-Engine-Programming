#ifndef SYS_PTR_H
#define SYS_PTR_H

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
struct List;

template <typename T>
struct Vector;

template <typename T>
struct Weak;

struct EnablePtr
{
  EnablePtr()
  { }

  EnablePtr(const EnablePtr& _copy)
  { }

  EnablePtr& operator=(const EnablePtr& _other)
  {
    return *this;
  }

/*
  ~EnablePtr()
  {
    if(m_lock.count())
    {
      panic("Invalid lock [TODO: Remove me]");
    }
  }
*/

private:
  template <typename T>
  friend struct Ptr;

  template <typename T>
  friend struct List;

  template <typename T>
  friend struct Vector;

  LockBlock m_lock;
};

template <typename T>
struct Ptr
{
  Ptr();

  template <typename U> Ptr(const Ptr<U>& _other);
  template <typename U> Ptr& operator=(const Ptr<U>& _other);

  Ptr(T* _t);
  Ptr& operator=(T* _other);

  //Ptr(const PtrLock<T>& _lock);
  //Ptr& operator=(const PtrLock<T>& _lock);
  //template <typename U> Ptr(const PtrLock<U>& _other);
  //template <typename U> Ptr& operator=(const PtrLock<U>& _other);

  //Ptr(const Unique<T>& _unique);
  //Ptr& operator=(const Unique<T>& _unique);
  template <typename U> Ptr(const Unique<U>& _unique);
  template <typename U> Ptr& operator=(const Unique<U>& _unique);

  template <typename U> Ptr(const Weak<U>& _other);
  template <typename U> Ptr& operator=(const Weak<U>& _other);

#ifdef SYS_DEBUG
  RefLock<T> operator*() const;
  PtrLock<T> operator->() const;
#else
  T& operator*() const;
  T* operator->() const;
#endif

  //bool operator==(const Ptr& _other) const;
  //bool operator!=(const Ptr& _other) const;

  bool operator==(T* _other) const;
  bool operator!=(T* _other) const;

  template <typename U> bool operator==(const Ptr<U>& _other) const;
  template <typename U> bool operator!=(const Ptr<U>& _other) const;

  T* unsafe_raw() const;
  void reset();

  template <typename U> Ptr<U> cast() const;

private:
  // TODO: Rename this
  typedef void (Ptr::*BoolType)() const;
  void this_type_does_not_support_comparisons() const {}

public:
  operator BoolType() const;

private:
  template <typename U>
  friend struct List;

  template <typename U>
  friend struct Vector;

  template <typename U>
  friend struct Ptr;

  template <typename U>
  friend struct RefLock;

  Zero<T*> m_ptr;
  Lock m_lock;

};

}

/* Implementation */

#include "Unique.h"

namespace sys
{

template <typename T>
Ptr<T>::Ptr()
{ }

template <typename T>
Ptr<T>::Ptr(T* _t) :
  m_ptr(_t),
  m_lock(_t ? &_t->m_lock : NULL)
{ }

template <typename T>
Ptr<T>& Ptr<T>::operator=(T* _other)
{
  const LockBlock* olb = _other ? &_other->m_lock : NULL;

  if(m_ptr != _other ||
    m_lock.block() != olb)
  {
    m_ptr = _other;
    m_lock.lock(olb);
  }

  return *this;
}

/*
template <typename T>
Ptr<T>::Ptr(const Unique<T>& _unique) :
  m_ptr(_unique.m_ptr),
  m_lock(_unique.m_lock)
{ }
*/

/*
template <typename T>
Ptr<T>& Ptr<T>::operator=(const Unique<T>& _unique)
{
  m_ptr = _unique.m_ptr;
  m_lock.lock(_unique.m_lock);

  return *this;
}
*/

/*
template <typename T>
Ptr<T>::Ptr(const PtrLock<T>& _lock) :
  m_ptr(_lock.m_ptr),
  m_lock(_lock.m_lock)
{ }
*/

// TODO: Shall we make non-template version? Is synthesised version safe?

template <typename T>
template <typename U>
Ptr<T>::Ptr(const Ptr<U>& _other) :
  m_ptr(_other.m_ptr),
  m_lock(_other.m_lock)
{ }

template <typename T>
template <typename U>
Ptr<T>& Ptr<T>::operator=(const Ptr<U>& _other)
{
  if(m_ptr != _other.m_ptr ||
    m_lock.block() != _other.m_lock.block())
  {
    m_ptr = _other.m_ptr;
    m_lock = _other.m_lock;
  }

  return *this;
}

template <typename T>
template <typename U>
Ptr<T>::Ptr(const Unique<U>& _unique) :
  m_ptr(_unique.m_ptr),
  m_lock(_unique.m_lock)
{ }
 
template <typename T>
template <typename U>
Ptr<T>& Ptr<T>::operator=(const Unique<U>& _unique)
{
  m_ptr = _unique.m_ptr;
  m_lock.lock(_unique.m_lock);

  return *this;
}

// TODO: Do we need to check m_rc if m_ptr is valid?

template <typename T>
template <typename U>
Ptr<T>::Ptr(const Weak<U>& _other) :
  m_ptr((_other.m_rc && _other.m_rc->strong) ? _other.m_ptr : NULL),
  m_lock(_other.m_rc ? &_other.m_rc->lock : NULL)
{ }

template <typename T>
template <typename U>
Ptr<T>& Ptr<T>::operator=(const Weak<U>& _weak)
{
  m_ptr = (_weak.m_rc && _weak.m_rc->strong) ? _weak.m_ptr : NULL;
  m_lock.lock(_weak.m_rc ? _weak.m_rc->lock : NULL);

  return *this;
}

/*
template <typename T>
Ptr<T>& Ptr<T>::operator=(const PtrLock<T>& _lock)
{
  m_ptr = _lock.m_ptr;
  m_lock = _lock.m_lock;

  return *this;
}
*/

template <typename T>
template <typename U>
bool Ptr<T>::operator==(const Ptr<U>& _other) const
{
  return m_ptr == _other.m_ptr;
}

template <typename T>
template <typename U>
bool Ptr<T>::operator!=(const Ptr<U>& _other) const
{
  return m_ptr != _other.m_ptr;
}

template <typename T>
bool Ptr<T>::operator==(T* _other) const
{
  return m_ptr == _other;
}

template <typename T>
bool Ptr<T>::operator!=(T* _other) const
{
  return m_ptr != _other;
}

template <typename T>
template <typename U>
Ptr<U> Ptr<T>::cast() const
{
  // TODO: Clean
  Ptr<U> rtn;
  rtn.m_ptr = dynamic_cast<U*>(static_cast<T*>(m_ptr));

  if(rtn.m_ptr)
  {
    rtn.m_lock = m_lock;
  }

  return rtn;
}

#ifdef SYS_DEBUG
template <typename T>
RefLock<T> Ptr<T>::operator*() const
{
  return RefLock<T>(m_ptr, m_lock.block());
}

template <typename T>
PtrLock<T> Ptr<T>::operator->() const
{
  return PtrLock<T>(m_ptr, m_lock.block());
}
#else
template <typename T>
T& Ptr<T>::operator*() const
{
  return *m_ptr;
}

template <typename T>
T* Ptr<T>::operator->() const
{
  return m_ptr;
}
#endif

/*
template <typename T>
bool Ptr<T>::operator==(const Ptr& _other) const
{
  return m_ptr == _other.m_ptr;
}

template <typename T>
bool Ptr<T>::operator!=(const Ptr& _other) const
{
  return m_ptr != _other.m_ptr;
}
*/

template <typename T>
T* Ptr<T>::unsafe_raw() const
{
  return m_ptr;
}

template <typename T>
void Ptr<T>::reset()
{
  m_lock.lock(NULL);
  m_ptr = NULL;
}

template <typename T>
Ptr<T>::operator BoolType() const
{
  if(m_ptr)
  {
    return &Ptr::this_type_does_not_support_comparisons;
  }

  return NULL;
}

}

#endif

