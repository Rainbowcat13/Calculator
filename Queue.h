#ifndef QUEUE_H
#define QUEUE_H

#include "ListNode.h"

template <typename T> class Queue {
public:
  Queue();
  Queue(const Queue<T> &);
  ~Queue();
  void push(const T &);
  const T &front() const;
  T pop();
  bool isEmpty() const;
  void clear();
  Queue<T> &operator=(const Queue<T> &);

private:
  ListNode<T> *head, *tail;
};

template <typename T> Queue<T>::Queue() {
  head = nullptr;
  tail = nullptr;
}

template <typename T> Queue<T>::Queue(const Queue<T> &q) {
  head = ListNode<T>::cloneList(q.head);
  tail = ListNode<T>::endOfList(head);
}

template <typename T> Queue<T>::~Queue() { clear(); }

template <typename T> void Queue<T>::push(const T &ref) {
  if (isEmpty()) {
    head = new ListNode<T>(ref);
    tail = head;
  } else {
    tail->next = new ListNode<T>(ref);
    tail = tail->next;
  }
}

template <typename T> const T &Queue<T>::front() const { return head->value; }

template <typename T> T Queue<T>::pop() {
  T result = head->value;
  ListNode<T> *old = head;
  head = head->next;
  delete old;
  return result;
}

template <typename T> bool Queue<T>::isEmpty() const { return head == nullptr; }

template <typename T> void Queue<T>::clear() {
  ListNode<T>::clearList(head);
  tail = nullptr;
}

template <typename T> Queue<T> &Queue<T>::operator=(const Queue<T> &q) {
  clear();
  head = ListNode<T>::cloneList(q.head);
  tail = ListNode<T>::endOfList(head);
  return *this;
}

#endif
