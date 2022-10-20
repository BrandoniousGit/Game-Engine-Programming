#include "Zero.h"
#include "Exception.h"
#include "Lock.h"
#include "config.h"

namespace sys
{

template <typename T>
struct Weak;

template <typename T>
struct Ptr;

struct Rc
{
  Zero<int> strong;
  Zero<int> weak;
  LockBlock lock;
};

struct EnableWeak
{
  EnableWeak() :
    m_rc(new Rc())
  {
    if(!m_rc)
    {
      throw Exception("Failed to allocate reference count");
    }

    ++m_rc->strong;
  }

  EnableWeak(const EnableWeak& _copy) :
    m_rc(new Rc())
  {
    if(!m_rc)
    {
      throw Exception("Failed to allocate reference count");
    }

    ++m_rc->strong;
  }

  EnableWeak& operator=(const EnableWeak& _other)
  {
    return *this;
  }

  ~EnableWeak()
  {
    --m_rc->strong;

    if(!m_rc->weak)
    {
      delete m_rc;
    }
  }

private:
  template <typename U>
  friend struct Weak;

  Zero<Rc*> m_rc;
};

template <typename T>
struct Weak
{
  Weak();
  Weak(const Weak& _copy);
  Weak& operator=(const Weak& _other);
  ~Weak();

  Weak(T* _ptr);
  Weak(Ptr<T> _ptr);

#ifdef SYS_DEBUG
  PtrLock<T> operator->() const;
#else
  T* operator->() const;
#endif

private:
  template <typename U>
  friend struct Ptr;

  Zero<T*> m_ptr;
  Zero<Rc*> m_rc;
};

}

/* Implementation */

#include "Ptr.h"

namespace sys
{

template <typename T>
Weak<T>::Weak()
{ }

template <typename T>
Weak<T>::Weak(const Weak& _copy) :
  m_ptr(_copy.m_ptr),
  m_rc(_copy.m_rc)
{
  if(m_rc)
  {
    ++m_rc->weak;
  }
}

template <typename T>
Weak<T>& Weak<T>::operator=(const Weak& _other)
{
  Weak tmp(*this);

  if(m_rc)
  {
    --m_rc->weak;
  }

  m_ptr = _other.m_ptr;
  m_rc = _other.m_rc;

  if(m_rc)
  {
    ++m_rc->weak;
  }

  return *this;
}

template <typename T>
Weak<T>::~Weak()
{
  if(m_rc)
  {
    --m_rc->weak;

    if(!m_rc->strong && !m_rc->weak)
    {
      delete m_rc;
    }
  }
}

template <typename T>
Weak<T>::Weak(T* _ptr) :
  m_ptr(_ptr)
{
  if(m_ptr)
  {
    m_rc = m_ptr->m_rc;
    ++m_rc->weak;
  }
}

template <typename T>
Weak<T>::Weak(Ptr<T> _ptr) :
  m_ptr(_ptr.unsafe_raw())
{
  if(m_ptr)
  {
    m_rc = m_ptr->m_rc;
    ++m_rc->weak;
  }
}

#ifdef SYS_DEBUG
template <typename T>
PtrLock<T> Weak<T>::operator->() const
{
  if(!m_ptr || !m_rc || !m_rc->strong)
  {
    sys::panic("Attempt to dereference NULL pointer");
  }

  return PtrLock<T>(m_ptr, m_rc->lock);
}

#else
template <typename T>
T* Weak<T>::operator->() const
{
  if(!m_ptr || !m_rc || !m_rc->strong)
  {
    sys::panic("Attempt to dereference NULL pointer");
  }

  return m_ptr;
}
#endif

}

