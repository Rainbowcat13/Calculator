#ifndef LIST_H
#define LIST_H

#include "ListNode.h"
#include <stdexcept>

template <typename T> class List {
public:
  List();
  List(const List<T> &);
  ~List();
  T &insert(const T &, unsigned int);
  T remove(unsigned int);
  void clear();
  unsigned int size() const;
  bool isEmpty() const;
  T &operator[](unsigned int);
  const T &operator[](unsigned int) const;

private:
  ListNode<T> *head;
  unsigned int count;
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

template <typename T> T &List<T>::insert(const T &e, unsigned int i) {
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

template <typename T> T List<T>::remove(unsigned int i) {
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

template <typename T> unsigned int List<T>::size() const { return count; }

template <typename T> bool List<T>::isEmpty() const { return count == 0; }

template <typename T> T &List<T>::operator[](unsigned int i) {
  if (i >= count)
    throw std::out_of_range("invalid index");
  ListNode<T> *n = head;
  while ((i--) > 0)
    n = n->next;
  return n->value;
}

template <typename T> const T &List<T>::operator[](unsigned int i) const {
  if (i >= count)
    throw std::out_of_range("invalid index");
  ListNode<T> *n = head;
  while ((i--) > 0)
    n = n->next;
  return n->value;
}

#endif
