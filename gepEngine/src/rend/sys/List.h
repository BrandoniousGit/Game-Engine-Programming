#ifndef SYS_LIST_H
#define SYS_LIST_H

#include "Ptr.h"
#include "panic.h"

namespace sys
{

template <typename T>
struct Ptr;

template <typename T>
struct List : EnablePtr
{
private:
  struct Node : EnablePtr
  {
    Node();
    Node(const T& _value);

    T m_value;
    Ptr<Node> m_next;
    Ptr<Node> m_prev;
  };

public:
  struct Iterator
  {
    Iterator& operator++();
    bool operator!=(const Iterator& _other) const;
    bool operator==(const Iterator& _other) const;
    PtrLock<T> operator->() const;
    RefLock<T> operator*() const;

    //operator Ptr<T>() const;

  private:
    template <typename U>
    friend struct List;

    Ptr<Node> m_node;
    Zero<bool> m_end;
  };

  List();
  List(const List& _copy);
  ~List();
  Ptr<T> push(const T& _value);
  Ptr<T> emplace();
  void clear();
  Iterator begin() const;
  Iterator end() const;
  Iterator erase(Iterator& _it);

private:
  Ptr<Node> m_first;
  Ptr<Node> m_last;

  // TODO: List assignment should be possible
  List& operator=(const List& _other);

};

template <typename T>
List<T>::Node::Node()
{ }

template <typename T>
List<T>::Node::Node(const T& _value) :
  m_value(_value)
{ }

#define REF_LIST_ATTACH           \
  if(m_last)                      \
  {                               \
    node->m_prev = m_last;        \
    m_last->m_next = node;        \
    m_last = node;                \
  }                               \
  else                            \
  {                               \
    m_first = node;               \
    m_last = node;                \
  }                               \
                                  \
  Ptr<T> rtn;                     \
  rtn.m_ptr = &node->m_value;     \
  rtn.m_lock.lock(&node->m_lock); \
                                  \
  return rtn;

template <typename T>
Ptr<T> List<T>::push(const T& _value)
{
  Ptr<Node> node = new Node(_value);

  REF_LIST_ATTACH
}

template <typename T>
Ptr<T> List<T>::emplace()
{
  Ptr<Node> node = new Node();

  REF_LIST_ATTACH
}

template <typename T>
List<T>::List()
{ }

template <typename T>
List<T>::List(const List& _copy)
{
  for(typename List::Iterator it = _copy.begin(); it != _copy.end(); ++it)
  {
    push(*it);
  }
}

template <typename T>
List<T>::~List()
{
  clear();
}

template <typename T>
void List<T>::clear()
{
  Ptr<Node> curr = m_first;

  m_first = NULL;
  m_last = NULL;

  while(curr)
  {
    Ptr<Node> next = curr->m_next;

    if(next)
    {
      next->m_prev = NULL;
    }

    Node* raw = curr.unsafe_raw();
    curr = next;
    delete raw;
  }
}

/*
template <typename T>
List<T>::Iterator::operator Ptr<T>() const
{
  if(m_end)
  {
    sys::panic("Dereferencing end node");
  }

  Ptr<T> rtn;
  rtn.m_ptr = &m_node->m_value;
  rtn.m_lock.lock(&m_node->m_lock);

  return rtn;
}
*/

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++()
{
  if(m_end)
  {
    sys::panic("Iteration past end");
  }

  Ptr<Node> next = m_node->m_next;

  if(!next)
  {
    m_end = true;
    m_node = NULL;
  }
  else
  {
    m_node = next;
  }

  return *this;
}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator& _other) const
{
  bool rtn = m_node == _other.m_node && m_end == _other.m_end;

  return !rtn;
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator& _other) const
{
  bool rtn = m_node == _other.m_node && m_end == _other.m_end;

  return rtn;
}

template <typename T>
PtrLock<T> List<T>::Iterator::operator->() const
{
  return PtrLock<T>(&m_node->m_value, &m_node->m_lock);
}

template <typename T>
RefLock<T> List<T>::Iterator::operator*() const
{
  return RefLock<T>(&m_node->m_value, &m_node->m_lock);
}

template <typename T>
typename List<T>::Iterator List<T>::begin() const
{
  if(!m_first)
  {
    return end();
  }

  Iterator rtn;
  rtn.m_node = m_first;

  return rtn;
}

template <typename T>
typename List<T>::Iterator List<T>::end() const
{
  Iterator rtn;
  //rtn.m_node = m_last;
  rtn.m_end = true;

  return rtn;
}

template <typename T>
typename List<T>::Iterator List<T>::erase(Iterator& _it)
{
  Node* node = _it.m_node.unsafe_raw();

  if(node->m_prev && node->m_next)
  {
    node->m_prev->m_next = node->m_next;
    node->m_next->m_prev = node->m_prev;
  }
  else if(node->m_prev)
  {
    node->m_prev->m_next = NULL;
  }
  else if(node->m_next)
  {
    node->m_next->m_prev = NULL;
  }

  if(!node->m_prev)
  {
    m_first = node->m_next;
  }

  if(!node->m_next)
  {
    m_last = node->m_prev;
  }

  ++_it;
  delete node;

  return _it;
}

}

#endif

