#ifndef HASH_H
#define HASH_H

#include <string>

template <typename T> class Hash {
public:
  unsigned long operator()(const T &) const;
};

template<>
class Hash<std::string> {
  public:
    unsigned long operator()(const std::string &s) const;
};

template <typename T> unsigned long Hash<T>::operator()(const T &t) const {
  return static_cast<unsigned long>(t);
}

#endif
