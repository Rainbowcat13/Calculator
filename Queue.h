#ifndef QUEUE_H
#define QUEUE_H

#include "ListNode.h"

template<typename T>
class Queue {
  public:
    Queue() {}
    Queue(const Queue<T> &);
    void push(T);
    T top();
    T pop();
    bool isEmpty();
    void clear();
  private:
    ListNode<T> *head = nullptr, *tail = nullptr;
};

template<typename T>
Queue<T>::Queue(const Queue<T> &q) {
  auto cloned = clone(q.head);
  head = cloned.first;
  tail = cloned.second;
}

template<typename T>
void Queue<T>::push(T value) {
  auto *newNode = new ListNode<T>(value);
  if (isEmpty()) {
    head = tail = newNode;
  } else {
    tail = tail->next = newNode;
  }
}

template<typename T>
T Queue<T>::top() {
  return head->value;
}

template<typename T>
T Queue<T>::pop() {
  T result = head->value;
  ListNode<T> *oldHead = head;
  head = head->next;
  delete oldHead;
  return result;
}

template<typename T>
bool Queue<T>::isEmpty() {
  return head == nullptr;
}

template<typename T>
void Queue<T>::clear() {
  clear(head);
  head = nullptr;
}

#endif

