#ifndef SYS_LOCK_H
#define SYS_LOCK_H

#include "panic.h"
#include "Zero.h"
#include "config.h"

#include <typeinfo>

namespace sys
{

/***************************************************************************
 * LockBlock
 *
 * Acts as a store for the lock count which can be incremented and
 * decremented.
 ***************************************************************************/
struct LockBlock
{
  LockBlock()
  { }

  ~LockBlock()
  {
#ifdef SYS_DEBUG
    if(m_count != 0)
    {
      panic("Resource is locked during destruction");
    }
#endif
  }

  int count() const
  {
    return m_count;
  }

  void increment() const
  {
#ifdef SYS_DEBUG
    ++m_count;
#endif
  }

  void decrement() const
  {
#ifdef SYS_DEBUG
    if(!m_count)
    {
      panic("Cannot decrease count less than 0");
    }

    --m_count;
#endif
  }

  mutable Zero<const char*> type_name;

private:
  mutable Zero<int> m_count;

  LockBlock(const LockBlock& _copy);
  LockBlock& operator=(const LockBlock& _other);

};

struct Lock
{
  Lock()
  { }

  Lock(const Lock& _copy) :
    m_block(_copy.m_block)
  {
    if(m_block)
    {
      m_block->increment();
    }
  }

  Lock(const LockBlock* _block) :
    m_block(_block)
  {
    if(m_block)
    {
      m_block->increment();
    }
  }

  Lock& operator=(const Lock& _other)
  {
    if(this != &_other)
    {
      if(m_block) m_block->decrement();
      m_block = _other.m_block;
      if(m_block) m_block->increment();
    }

    //lock(_other.m_block);

    return *this;
  }

  ~Lock()
  {
    if(m_block)
    {
      m_block->decrement();
    }
  }

  void lock(const LockBlock* _block) const
  {
    if(m_block == _block) return;

    if(m_block)
    {
      m_block->decrement();
    }

    m_block = _block;

    if(m_block)
    {
      m_block->increment();
    }
  }

  void lock(const LockBlock& _block) const
  {
    lock(&_block);
  }

  const LockBlock* block() const
  {
    return m_block;
  }

private:
  mutable Zero<const LockBlock*> m_block;

};

template <typename T>
struct Ptr;

/***************************************************************************
 * PtrLock
 *
 * Hooks into the operator-> dereference and creates a wrapper object that
 * forwards through the T* but also increments a lock throughout the
 * lifespan of the object.
 ***************************************************************************/
template <typename T>
struct PtrLock
{
  PtrLock(T* _ptr, const LockBlock* _lock);

  T* operator->() const;

private:
  template <typename U>
  friend struct Ptr;

  Zero<T*> m_ptr;
  Lock m_lock;
};

/***************************************************************************
 * RefLock
 ***************************************************************************/
template <typename T>
struct Ref;

template <typename T>
struct RefLock
{
  RefLock(T* _ptr, const LockBlock* _lock);

  operator T&() const;
  T* operator&() const;

  // TODO: This one required?
  T* operator->() const;

private:
  template <typename U>
  friend struct Ref;

  Zero<T*> m_ptr;
  Lock m_lock;
};

/***************************************************************************
 * IndexLock
 *
 * Hooks into the array operator[] in that it creates a temporary object
 * which passes through an array index variable whilst at the same time
 * incrementing the lock during the lifespan of the wrapper object.
 ***************************************************************************/
struct IndexLock
{
  IndexLock(size_t _index) :
    m_index(_index)
  { }

  operator size_t() const
  {
    return m_index;
  }

  void lock(const LockBlock* _lock) const
  {
    m_lock.lock(_lock);
  }

private:
  Zero<size_t> m_index;
  Lock m_lock;

  IndexLock(const IndexLock& _copy);
  IndexLock& operator=(const IndexLock& _other);
};

}

/* Implementation */

namespace sys
{

/***************************************************************************
 * PtrLock
 *
 * Construct PtrLock by assigning all variables. The internal lock also
 * increments the LockBlock reference count.
 ***************************************************************************/
template <typename T>
PtrLock<T>::PtrLock(T* _ptr, const LockBlock* _lock) :
  m_ptr(_ptr),
  m_lock(_lock)
{ }

template <typename T>
T* PtrLock<T>::operator->() const
{
  if(!m_ptr) panic("Attempting to dereference NULL pointer");
  return m_ptr;
}

template <typename T>
RefLock<T>::RefLock(T* _ptr, const LockBlock* _lock) :
  m_ptr(_ptr),
  m_lock(_lock)
{ }

template <typename T>
RefLock<T>::operator T&() const
{
  if(!m_ptr) panic("Attempting to dereference NULL pointer");
  return *m_ptr;
}

template <typename T>
T* RefLock<T>::operator&() const
{
  if(!m_ptr) panic("Attempting to dereference NULL pointer");
  return m_ptr;
}

template <typename T>
T* RefLock<T>::operator->() const
{
  if(!m_ptr) panic("Attempting to dereference NULL pointer");
  return *m_ptr;
}

}

#endif

