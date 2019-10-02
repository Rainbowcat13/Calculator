#ifndef PAIR_H
#define PAIR_H

template <typename T, typename U> struct Pair {
  Pair(T = T(), U = U());
  T first;
  U second;
};

template <typename T, typename U> Pair<T, U>::Pair(T f, U s) {
  first = f;
  second = s;
}

#endif
