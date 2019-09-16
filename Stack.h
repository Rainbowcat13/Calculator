#ifndef STACK_H
#define STACK_H

#include "ListNode.h"

template<typename T>
class Stack {
  public:
    Stack() {}
    Stack(const Stack<T> &);
    void push(T);
    T top();
    T pop();
    bool isEmpty();
    void clear();
  private:
    ListNode<T> *head = nullptr;
};

template<typename T>
Stack<T>::Stack(const Stack<T> &s) {
  head = clone(s.head).first;
}

template<typename T>
void Stack<T>::push(T value) {
  head = new ListNode<T>(value, head);
}

template<typename T>
T Stack<T>::top() {
  return head->value;
}

template<typename T>
T Stack<T>::pop() {
  T result = head->value;
  ListNode<T> *oldHead = head;
  head = head->next;
  delete oldHead;
  return result;
}

template<typename T>
bool Stack<T>::isEmpty() {
  return head == nullptr;
}

template<typename T>
void Stack<T>::clear() {
  clear(head);
  head = nullptr;
}

#endif

