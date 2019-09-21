#ifndef HASH_H
#define HASH_H

template<typename T>
class Hash {
  public:
    unsigned long operator()(const T &) const;
};

template<typename T>
unsigned long Hash<T>::operator()(const T &t) const {
  return static_cast<unsigned long>(t);
}

#endif

