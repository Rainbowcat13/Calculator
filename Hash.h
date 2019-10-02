<<<<<<< HEAD
#ifndef HASH_H
#define HASH_H

template <typename T> class Hash {
public:
  unsigned long operator()(const T &) const;
};

template <typename T> unsigned long Hash<T>::operator()(const T &t) const {
  return static_cast<unsigned long>(t);
}

#endif
=======
#ifndef HASH_H
#define HASH_H

#include <string>

template <typename T> class Hash {
public:
  unsigned long operator()(const T &) const;
};

template <> class Hash<std::string> {
public:
  unsigned long operator()(const std::string &s) const;
};

template <typename T> unsigned long Hash<T>::operator()(const T &t) const {
  return static_cast<unsigned long>(t);
}

#endif
>>>>>>> cc4f7a71590d8d6f35516dc65ef1573b9b2a42e3
