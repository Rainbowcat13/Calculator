#ifndef LISTNODE_H
#define LISTNODE_H

#include "Pair.h"

template<typename T>
struct ListNode {
  explicit ListNode(T value, ListNode *next = nullptr) : value(value), next(next) {}
  T value;
  ListNode *next;
};

template<typename T>
Pair<ListNode<T> *, ListNode<T> *> clone(ListNode<T> *n) {
  if (n == nullptr) return Pair<ListNode<T> *, ListNode<T> *>(nullptr, nullptr);
  auto cloned = clone(n->next);
  auto newNode = new ListNode<T>(n->value, cloned.first);
  return Pair<ListNode<T> *, ListNode<T> *>(newNode, cloned.second);
}

template<typename T>
void clear(ListNode<T> *n) {
  if (n == nullptr) return;
  clear(n->next);
  delete n;
}

#endif

