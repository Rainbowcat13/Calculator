#ifndef STACK_H
#define STACK_H

#include "ListNode.h"

template <typename T> class Stack {
public:
  Stack();
  Stack(const Stack<T> &);
  ~Stack();
  void push(const T &);
  const T &top() const;
  T pop();
  bool isEmpty() const;
  void clear();
  Stack<T> &operator=(const Stack<T> &);

private:
  ListNode<T> *head;
};

template <typename T> Stack<T>::Stack() { head = nullptr; }

template <typename T> Stack<T>::Stack(const Stack<T> &s) {
  head = ListNode<T>::cloneList(s.head);
}

template <typename T> Stack<T>::~Stack() { clear(); }

template <typename T> void Stack<T>::push(const T &ref) {
  head = new ListNode<T>(ref, head);
}

template <typename T> const T &Stack<T>::top() const {
  if (isEmpty())
    throw std::out_of_range("stack is empty");
  return head->value;
}

template <typename T> T Stack<T>::pop() {
  if (isEmpty())
    throw std::out_of_range("stack is empty");
  T result = head->value;
  ListNode<T> *old = head;
  head = head->next;
  delete old;
  return result;
}

template <typename T> bool Stack<T>::isEmpty() const { return head == nullptr; }

template <typename T> void Stack<T>::clear() { ListNode<T>::clearList(head); }

template <typename T> Stack<T> &Stack<T>::operator=(const Stack<T> &s) {
  clear();
  head = ListNode<T>::cloneList(s.head);
  return *this;
}

#endif
