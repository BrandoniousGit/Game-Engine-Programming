#ifndef SYS_PRIVATE_H
#define SYS_PRIVATE_H

namespace sys
{

template <typename T>
struct RcPtr
{
  static void do_delete(void* _ptr)
  {
    T* t = (T*)_ptr;
    delete t;
  }

  T* ptr;
  void (*deleter)(void* _ptr);
};

struct Rc
{
  int* m_rc;

  Rc() :
    m_rc(new int(1))
  { }

  ~Rc()
  {
    --*m_rc;

    if(!*m_rc)
    {
      delete m_rc;
    }
  }

  Rc(const Rc& _copy) :
    m_rc(_copy.m_rc)
  {
    ++*m_rc;
  }

  Rc& operator=(const Rc& _other)
  {
    Rc tmp(*this);
    --*m_rc;

    m_rc = _other.m_rc;
    ++*m_rc;

    return *this;
  }

  int count() const
  {
    return *m_rc;
  }
};

template <typename T>
struct EnablePrivate
{
  EnablePrivate() :
    m_rc(),
    m_ptr(new RcPtr<T>())
  { }

  ~EnablePrivate()
  {
    if(m_rc.count() == 1)
    {
      if(m_ptr->deleter)
      {
        m_ptr->deleter(m_ptr->ptr);
      }

      delete m_ptr;
    }
  }

  EnablePrivate(const EnablePrivate& _copy) :
    m_rc(_copy.m_rc),
    m_ptr(_copy.m_ptr)
  { }

  EnablePrivate& operator=(const EnablePrivate& _other)
  {
    EnablePrivate tmp(*this);

    m_rc = _other.m_rc;
    m_ptr = _other.m_ptr;

    return *this;
  }

protected:
  Rc m_rc;
  RcPtr<T>* m_ptr;

  T* self()
  {
    if(!m_ptr->ptr)
    {
      m_ptr->ptr = new T();
      m_ptr->deleter = RcPtr<T>::do_delete;
    }

    return m_ptr->ptr;
  }

  T* operator->()
  {
    return self();
  }

  T& operator*()
  {
    return *self();
  }
};

}

#define EnablePrivate EnablePrivate<struct Private>
#define self self()

#endif

