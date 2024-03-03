#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include "listIterator.hpp"
#include "node.hpp"

namespace doroshenko
{
  template <typename T>
  class List
  {
  public:
    Node<T>* head_;
    Node<T>* tail_;

    List();
    List(const List< T >& otherList) = default;
    List(List< T >&& otherList) = default;
    ~List();

    void pushFront(const T& data);
    void pushBack(const T& data);
    void popFront();
    bool isEmpty();
    void clear();
    void swap(List<T>& otherList);
    void assign(size_t n, const T& value);
    //void remove(const T& value);
    //void removeIf();
    size_t getSize();

    Node<T>* operator[](const int index);

    ListIterator<T> begin() const;
    ListIterator<T> end() const;

    const ListIterator<T> cbegin() const;
    const ListIterator<T> cend() const;
  };
}

template< typename T >
doroshenko::List<T>::List() :
  head_(nullptr),
  tail_(nullptr)
{}

template< typename T >
doroshenko::List<T>::~List()
{
  clear();
  delete head_;
  delete tail_;
}

template< typename T >
void doroshenko::List<T>::pushFront(const T& data)
{
  Node<T>* node = new Node<T>(data);
  if (head_!=nullptr)
  {
    node->next = head_;
    head_ = node;
  }
  else
  {
    head_ = tail_ = node;
  }
}

template< typename T >
void doroshenko::List<T>::pushBack(const T& data)
{
  Node<T>* node = new Node<T>(data);
  if (head_ == nullptr)
  {
    head_ = tail_ = node;
  }
  else
  {
    tail_->next = node;
    tail_ = node;
  }
}

template< typename T >
size_t doroshenko::List<T>::getSize()
{
  doroshenko::Node<T>* head = head_;
  size_t size = 0ull;
  while (head)
  {
    size++;
    head = head->next;
  }
  return size;
}


template< typename T >
void doroshenko::List<T>::popFront()
{
  if (head_ == tail_)
  {
    delete tail_;
    head_ = tail_ = nullptr;
  }
  if (head_ != nullptr)
  {
    Node<T>* node = head_;
    head_ = node->next;
    delete node;
  }
}

template<typename T>
bool doroshenko::List<T>::isEmpty()
{
  if (head_ == nullptr)
  {
    return true;
  }
  return false;
}

template< typename T >
void doroshenko::List<T>::clear()
{
  while (head_)
  {
    popFront();
  }
}

template< typename T >
void doroshenko::List<T>::swap(List<T>& otherList)
{
  doroshenko::Node<T>* head = head_;
  head_ = otherList.head_;
  otherList.head_ = head;
  delete head;
  doroshenko::Node<T>* tail = tail_;
  tail_ = otherList.tail_;
  otherList.tail_ = tail;
  delete tail;
}

template< typename T >
void doroshenko::List< T >::assign(size_t n, const T& value)
{
  for (size_t i = 0; i < n; i++)
  {
    push_back(value);
  }
}

template< typename T >
doroshenko::Node<T>* doroshenko::List<T>::operator[](const int index)
{
  if (isEmpty() == true)
  {
    return nullptr;
  }
  Node<T>* head = head_;
  for (int i = 0; i < index; i++)
  {
    head = head->next;
    if (!head)
    {
      return nullptr;
    }
  }
  return head;
}

template< typename T>
doroshenko::ListIterator<T> doroshenko::List<T>::begin() const
{
  return ListIterator<T>(head_);
}

template< typename T>
doroshenko::ListIterator<T> doroshenko::List<T>::end() const
{
  return ListIterator<T>(nullptr);
}

template< typename T>
const doroshenko::ListIterator<T> doroshenko::List<T>::cbegin() const
{
  return ListIterator<T>(head_);
}

template< typename T>
const doroshenko::ListIterator<T> doroshenko::List<T>::cend() const
{
  return ListIterator<T>(nullptr);
}

#endif
