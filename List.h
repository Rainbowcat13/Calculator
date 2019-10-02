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
  T &insertFront(const T &);
  T &insertBack(const T &);
  T &insert(const T &, std::size_t);
  T removeFront();
  T removeBack();
  T remove(std::size_t);
  void clear();
  std::size_t size() const;
  bool isEmpty() const;
  List<T> &operator=(const List<T> &);
  T &operator[](std::size_t);
  const T &operator[](std::size_t) const;

private:
  ListNode<T> *head, *iter;
  std::size_t count, iterIndex;
  ListNode<T> *findNode(std::size_t) const;
};

template <typename T> List<T>::List() {
  head = iter = nullptr;
  count = iterIndex = 0;
}

template <typename T> List<T>::List(const List<T> &l) {
  head = iter = ListNode<T>::cloneList(l.head);
  iterIndex = 0;
  count = l.count;
}

template <typename T> List<T>::~List() { clear(); }

template <typename T> T &List<T>::insertFront(const T &e) {
  head = new ListNode<T>(e, head);
  count++;
  iterIndex++;
  return head->value;
}

template <typename T> T &List<T>::insertBack(const T &e) {
  return insert(e, count);
}

template <typename T> T &List<T>::insert(const T &e, std::size_t i) {
  if (i == 0)
    return insertFront(e);
  ListNode<T> *n = findNode(i - 1);
  n->next = new ListNode<T>(e, n->next);
  count++;
  return n->next->value;
}

template <typename T> T List<T>::removeFront() {
  ListNode<T> *r = head;
  head = head->next;
  count--;
  if (iterIndex == 0)
    iter = head;
  else
    iterIndex--;
  T val = r->value;
  delete r;
  return val;
}

template <typename T> T List<T>::removeBack() { return remove(count - 1); }

template <typename T> T List<T>::remove(std::size_t i) {
  if (i == 0)
    return removeFront();
  ListNode<T> *n = findNode(i - 1);
  ListNode<T> *r = n->next;
  n->next = r->next;
  count--;
  T val = r->value;
  delete r;
  return val;
}

template <typename T> void List<T>::clear() {
  ListNode<T>::clearList(head);
  iter = nullptr;
  count = iterIndex = 0;
}

template <typename T> std::size_t List<T>::size() const { return count; }

template <typename T> bool List<T>::isEmpty() const { return count == 0; }

template <typename T> List<T> &List<T>::operator=(const List<T> &l) {
  clear();
  head = iter = ListNode<T>::cloneList(l.head);
  iterIndex = 0;
  count = l.count;
  return *this;
}

template <typename T> T &List<T>::operator[](std::size_t i) {
  return findNode(i)->value;
}

template <typename T> const T &List<T>::operator[](std::size_t i) const {
  return findNode(i)->value;
}

template <typename T> ListNode<T> *List<T>::findNode(std::size_t n) const {
  if (n >= count) {
    throw std::out_of_range("list index is out of range");
  } else if (n == 0) {
    return head;
  }
  std::size_t &i = const_cast<List<T> *>(this)->iterIndex;
  ListNode<T> *&it = const_cast<List<T> *>(this)->iter;
  if (it == nullptr || n < i) {
    i = 0;
    it = head;
  }
  for (; i < n; i++)
    it = it->next;
  return it;
}

#endif
