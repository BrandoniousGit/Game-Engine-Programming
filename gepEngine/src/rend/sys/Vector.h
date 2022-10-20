#ifndef SYS_VECTOR_H
#define SYS_VECTOR_H

#include "Ptr.h"
#include "Zero.h"
#include "Lock.h"

#include <new>

#ifdef _WIN32
  #include <BaseTsd.h>
  #define ssize_t SSIZE_T
#endif

namespace sys
{

template <typename T>
struct Ref;

template <typename T>
struct Vector : EnablePtr
{
  struct Iterator
  {
    Iterator& operator++();
    bool operator!=(const Iterator& _other) const;
    bool operator==(const Iterator& _other) const;
    PtrLock<T> operator->() const;
    RefLock<T> operator*() const;

  private:
    template <typename U>
    friend struct Vector;

    Zero<size_t> m_index;
    Ptr<const Vector> m_owner;
    Zero<bool> m_end;
    Lock m_lock;
  };

  Vector();
  Vector(size_t _size);

  Vector(const Vector& _copy);
  Vector& operator=(const Vector& _other);
  ~Vector();

#ifdef SYS_DEBUG
  T& operator[](const IndexLock& _index);
  const T& operator[](const IndexLock& _index) const;
#else
  T& operator[](size_t _index);
  const T& operator[](size_t _index) const;
#endif

  Ptr<T> get(size_t _index);
  Ptr<const T> get(size_t _index) const;

  Ptr<T> push(const T& _value);
  void clear();
  void resize(size_t _size);

  size_t size() const;

  T* unsafe_raw() const;

  Iterator begin() const;
  Iterator end() const;
  Iterator erase(Iterator& _it);

  void sort(bool (*_func)(T&, T&));

private:
  LockBlock m_locallock;
  Zero<size_t> m_total;
  Zero<T*> m_raw;
  Zero<size_t> m_size;

  void check_lock() const;
  void allocate(size_t _size);

  void quicksort(int _low, int _high, bool (*_func)(T&, T&));
  int partition(int _low, int _high, bool (*_func)(T&, T&));
  bool compareFunc(T& _a, T& _b);
  void swap(T& _a, T& _b);
};

}

/* Implementation */

#include "panic.h"

namespace sys
{

template <typename T>
Vector<T>::Vector() :
  m_total(8),
  m_raw(static_cast<T*>(calloc(m_total, sizeof(T))))
{
  if(!m_raw)
  {
    panic("Failed to allocate initial space");
  }
}

template <typename T>
Vector<T>::Vector(size_t _size)
{
  resize(_size);
}

template <typename T>
Vector<T>::Vector(const Vector& _copy) :
  m_total(_copy.m_size),
  m_raw(static_cast<T*>(calloc(m_total, sizeof(T))))
{
  if(!m_raw)
  {
    panic("Failed to allocate initial space");
  }

  try
  {
    for(size_t ei = 0; ei < _copy.m_size; ++ei)
    {
      new(&m_raw[ei]) T(_copy.m_raw[ei]);
      ++m_size;
    }
  }
  catch(...)
  {
    /* TODO: Can use clear() */
    for(ssize_t ei = m_size - 1; ei >= 0; --ei)
    {
      m_raw[ei].~T();
    }

    free(m_raw);

    throw;
  }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& _other)
{
  check_lock();

  size_t total = _other.m_size;
  T* raw = static_cast<T*>(calloc(total, sizeof(T)));
  size_t size = 0;

  if(!raw)
  {
    panic("Failed to allocate initial space");
  }

  try
  {
    for(size_t ei = 0; ei < _other.m_size; ++ei)
    {
      new(&raw[ei]) T(_other.m_raw[ei]);
      ++size;
    }
  }
  catch(...)
  {
    for(ssize_t ei = size - 1; ei >= 0; --ei)
    {
      raw[ei].~T();
    }

    free(raw);

    throw;
  }

  clear();
  free(m_raw);
  m_size = size;
  m_raw = raw;
  m_total = total;

  return *this;
}

template <typename T>
Vector<T>::~Vector()
{
  clear();
  free(m_raw);
}

#ifdef SYS_DEBUG
template <typename T>
T& Vector<T>::operator[](const IndexLock& _index)
{
  _index.lock(&m_locallock);

  if(_index >= m_size)
  {
    panic("Index out of bounds");
  }

  return m_raw[_index];
}

template <typename T>
const T& Vector<T>::operator[](const IndexLock& _index) const
{
  _index.lock(&m_locallock);

  if(_index >= m_size)
  {
    panic("Index out of bounds");
  }

  return m_raw[_index];
}
#else
template <typename T>
T& Vector<T>::operator[](size_t _index)
{
  return m_raw[_index];
}
     
template <typename T>
const T& Vector<T>::operator[](size_t _index) const
{ 
  return m_raw[_index];
}
#endif

template <typename T>
Ptr<T> Vector<T>::get(size_t _index)
{
#ifdef SYS_DEBUG
  if(_index >= m_size)
  {
    panic("Index out of bounds");
  }
#endif

  Ptr<T> rtn;

  rtn.m_ptr = &m_raw[_index];
  rtn.m_lock.lock(&m_locallock);

  return rtn;
}

template <typename T>
Ptr<const T> Vector<T>::get(size_t _index) const
{
#ifdef SYS_DEBUG
  if(_index >= m_size)
  {
    panic("Index out of bounds");
  }
#endif

  Ptr<const T> rtn;

  rtn.m_ptr = &m_raw[_index];
  rtn.m_lock.lock(&m_locallock);

  return rtn;
}

template <typename T>
Ptr<T> Vector<T>::push(const T& _value)
{
  check_lock();

  size_t size = m_size;
  allocate(size + 1);
  new(&m_raw[size]) T(_value);
  ++m_size;

  Ptr<T> rtn;

  rtn.m_ptr = &m_raw[size];
  rtn.m_lock.lock(&m_locallock);

  return rtn;
}

template <typename T>
size_t Vector<T>::size() const
{
  return m_size;
}

template <typename T>
void Vector<T>::clear()
{
  check_lock();

  for(ssize_t ei = m_size - 1; ei >= 0; --ei)
  {
    m_raw[ei].~T();
  }

  m_size = 0;
}

template <typename T>
void Vector<T>::resize(size_t _size)
{
  check_lock();

  if(_size > m_size)
  {
    allocate(_size);

    while(m_size != _size)
    {
      new(&m_raw[m_size]) T();
      ++m_size;
    }
  }
  else if(_size < m_size)
  {
    while(m_size != _size)
    {
      m_raw[m_size - 1].~T();
      --m_size;
    }
  }
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::erase(typename Vector<T>::Iterator& _it)
{
  if(_it.m_end)
  {
    sys::panic("Attempt to erase end iterator");
  }

  if(!m_size)
  {
    sys::panic("Attempt to erase from zero sized vector");
  }

  size_t index = _it.m_index;
  _it = Vector<T>::Iterator();

  for(size_t i = index; i < m_size - 1; ++i)
  {
    // TODO: Which is best?
    //m_raw[i] = m_raw[i + 1];

    m_raw[i].~T();
    new(&m_raw[i]) T(m_raw[i + 1]);
  }

  resize(m_size - 1);
  Iterator rtn(begin());

  for(size_t i = 0; i < index; ++i)
  {
    ++rtn;
  }

  _it = end();

  return rtn;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::begin() const
{
  if(!m_size)
  {
    return end();
  }

  Iterator rtn;

  rtn.m_index = 0;
  rtn.m_owner = this;
  rtn.m_lock.lock(&m_locallock);

  return rtn;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::end() const
{
  Iterator rtn;

  /* TODO: m_size might be 0! */
  rtn.m_index = m_size - 1;
  rtn.m_owner = this;
  rtn.m_end = true;

  return rtn;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
{
  if(m_index >= m_owner->size())
  {
    sys::panic("Iteration would go past end");
  }

  if(m_end)
  {
    sys::panic("Iteration past end");
  }

  ++m_index;

  if(m_index >= m_owner->m_size)
  {
    m_end = true;
    --m_index;
  }

  return *this;
}

template <typename T>
bool Vector<T>::Iterator::operator!=(const Iterator& _other) const
{
  bool rtn = m_index == _other.m_index &&
    m_end == _other.m_end &&
    m_owner == _other.m_owner;

  return !rtn;
}

template <typename T>
bool Vector<T>::Iterator::operator==(const Iterator& _other) const
{
  bool rtn = m_index == _other.m_index &&
    m_end == _other.m_end &&
    m_owner == _other.m_owner;

  return rtn;
}

template <typename T>
PtrLock<T> Vector<T>::Iterator::operator->() const
{
  return PtrLock<T>(&m_owner->m_raw[m_index],
    &m_owner->m_locallock);
}

template <typename T>
RefLock<T> Vector<T>::Iterator::operator*() const
{
  return RefLock<T>(&m_owner->m_raw[m_index],
    &m_owner->m_locallock);
}

template <typename T>
void Vector<T>::check_lock() const
{
  if(m_locallock.count() != 0)
  {
    panic("Invalidating locked resource");
  }
}

template <typename T>
void Vector<T>::allocate(size_t _size)
{
  if(m_total >= _size)
  {
    return;
  }

  size_t ns = 8;

  while(ns < _size)
  {
    ns *= 2;
  }

  size_t total = ns;
  T* raw = static_cast<T*>(calloc(total, sizeof(T)));
  size_t size = 0;

  if(!raw)
  {
    panic("Failed to allocate initial space");
  }

  try
  {
    for(size_t ei = 0; ei < m_size; ++ei)
    {
      new(&raw[ei]) T(m_raw[ei]);
      ++size;
    }
  }
  catch(...)
  {
    for(ssize_t ei = size - 1; ei >= 0; --ei)
    {
      raw[ei].~T();
    }

    free(raw);

    throw;
  }

  clear();
  free(m_raw);
  m_size = size;
  m_raw = raw;
  m_total = total;
}

template <typename T>
void Vector<T>::sort(bool (*_func)(T&, T&))
{
  quicksort(0, size() - 1, _func);
}

template <typename T>
void Vector<T>::swap(T& _a, T& _b)
{
  T t = _a;
  _a = _b;
  _b = t;
}

template <typename T>
bool Vector<T>::compareFunc(T& _a, T& _b)
{
  if(_a > _b)
  {
    return true;
  }

  return false;
}

template <typename T>
int Vector<T>::partition(int _low, int _high, bool (*_func)(T&, T&))
{
  int i = _low - 1;
  Vector<T>& self = *this;

  for(int j = _low; j <= _high - 1; ++j)
  {
    if(_func(self[j], self[_high]))
    {
      ++i;
      swap(self[i], self[j]);
    }
  }

  swap(self[i + 1], self[_high]);

  return i + 1;
}

template <typename T>
T* Vector<T>::unsafe_raw() const
{
  return &m_raw[0];
}

template <typename T>
void Vector<T>::quicksort(int _low, int _high, bool (*_func)(T&, T&))
{
  if(_low < _high)
  {
    int pivot = partition(_low, _high, _func);

    quicksort(_low, pivot - 1, _func);
    quicksort(pivot + 1, _high, _func);
  }
}

}

#endif

