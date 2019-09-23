#ifndef LISTNODE_H
#define LISTNODE_H

template <typename T> struct ListNode {
  static ListNode<T> *cloneList(ListNode<T> *);
  static ListNode<T> *endOfList(ListNode<T> *);
  static void clearList(ListNode<T> *&);
  explicit ListNode(const T &, ListNode<T> * = nullptr);
  T value;
  ListNode *next;
};

template <typename T> ListNode<T> *ListNode<T>::cloneList(ListNode<T> *n) {
  if (n == nullptr)
    return nullptr;
  return new ListNode<T>(n->value, cloneList(n->next));
}

template <typename T> ListNode<T> *ListNode<T>::endOfList(ListNode<T> *n) {
  if (n == nullptr)
    return nullptr;
  if (n->next == nullptr)
    return n;
  return endOfList(n->next);
}

template <typename T> void ListNode<T>::clearList(ListNode<T> *&n) {
  if (n == nullptr)
    return;
  clearList(n->next);
  delete n;
  n = nullptr;
}

template <typename T>
ListNode<T>::ListNode(const T &valRef, ListNode<T> *nextPtr) {
  value = valRef;
  next = nextPtr;
}

#endif
