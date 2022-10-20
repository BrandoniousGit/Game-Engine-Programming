#ifndef SYS_ZERO_H
#define SYS_ZERO_H

namespace sys
{

/***************************************************************************
 * Zero
 *
 * Provides a way for member variables to be initialized to Zero implicitly
 * rather than via initializer lists. Acts as a template wrapper class which
 * forwards through the contained internal variable but also initializing to
 * zero in its constructor.
 ***************************************************************************/
template <typename T>
struct Zero
{
  Zero();

  Zero(const T& _value);
  Zero& operator=(const T& _value);

  operator T&();
  operator const T&() const;

  T* operator&();
  const T* operator&() const;

  T operator->();
  const T operator->() const;

private:
  T m_value;
};

template <typename T>
Zero<T>::Zero() :
  m_value(0)
{ }

template <typename T>
Zero<T>::Zero(const T& _value) :
  m_value(_value)
{ }

template <typename T>
Zero<T>& Zero<T>::operator=(const T& _value)
{
  m_value = _value;

  return *this;
}

template <typename T>
Zero<T>::operator T&()
{
  return m_value;
}

template <typename T>
Zero<T>::operator const T&() const
{
  return m_value;
}

template <typename T>
T* Zero<T>::operator&()
{
  return &m_value;
}

template <typename T>
const T* Zero<T>::operator&() const
{
  return &m_value;
}

template <typename T>
T Zero<T>::operator->()
{
  return m_value;
}

template <typename T>
const T Zero<T>::operator->() const
{
  return m_value;
}

}

#endif

