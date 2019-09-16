#ifndef PAIR_H
#define PAIR_H

template<typename T, typename U>
struct Pair {
  Pair(T first = T(), U second = U()) : first(first), second(second) {}
  T first;
  U second;
};

#endif

