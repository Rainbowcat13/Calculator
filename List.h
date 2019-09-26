#ifndef LIST_H
#define LIST_H

#include "ListNode.h"
#include <cstddef>
#include <stdexcept>

template <typename T> class List {
public:
  List();
  List(const List<T> &);
  ~List();
  T &insert(const T &, std::size_t);
  T remove(std::size_t);
  void clear();
  std::size_t size() const;
  bool isEmpty() const;
  List<T> &operator=(const List<T> &);
  T &operator[](std::size_t);
  const T &operator[](std::size_t) const;

private:
  ListNode<T> *head;
  std::size_t count;
};

template <typename T> List<T>::List() {
  head = nullptr;
  count = 0;
}

template <typename T> List<T>::List(const List<T> &l) {
  head = ListNode<T>::cloneList(l.head);
  count = l.count;
}

template <typename T> List<T>::~List() { clear(); }

template <typename T> T &List<T>::insert(const T &e, std::size_t i) {
  if (i > count)
    throw std::out_of_range("invalid index");
  if (i == 0) {
    head = new ListNode<T>(e, head);
    count++;
    return head->value;
  }
  ListNode<T> *n = head;
  while ((i--) > 1)
    n = n->next;
  n->next = new ListNode<T>(e, n->next);
  count++;
  return n->next->value;
}

template <typename T> T List<T>::remove(std::size_t i) {
  if (i >= count)
    throw std::out_of_range("invalid index");
  if (i == 0) {
    ListNode<T> *r = head;
    head = head->next;
    count--;
    T val = r->value;
    delete r;
    return val;
  }
  ListNode<T> *n = head;
  while ((i--) > 1)
    n = n->next;
  ListNode<T> *r = n->next;
  n->next = r->next;
  count--;
  T val = r->value;
  delete r;
  return val;
}

template <typename T> void List<T>::clear() {
  ListNode<T>::clearList(head);
  count = 0;
}

template <typename T> std::size_t List<T>::size() const { return count; }

template <typename T> bool List<T>::isEmpty() const { return count == 0; }

template <typename T> List<T> &List<T>::operator=(const List<T> &l) {
  clear();
  head = ListNode<T>::cloneList(l.head);
  count = l.count;
  return *this;
}

template <typename T> T &List<T>::operator[](std::size_t i) {
  if (i >= count)
    throw std::out_of_range("invalid index");
  ListNode<T> *n = head;
  while ((i--) > 0)
    n = n->next;
  return n->value;
}

template <typename T> const T &List<T>::operator[](std::size_t i) const {
  if (i >= count)
    throw std::out_of_range("invalid index");
  ListNode<T> *n = head;
  while ((i--) > 0)
    n = n->next;
  return n->value;
}

#endif
