#ifndef STRING_H
#define STRING_H

#include "Hash.h"

class String {
public:
  String() {}
  String(const char *);
  String(const String &);
  ~String();
  const char *data() const;
  unsigned int length() const;
  bool isEmpty() const;
  bool operator==(const char *) const;
  bool operator==(const String &) const;
  char operator[](unsigned int) const;

private:
  unsigned int size;
  char *ptr;
};

template <> class Hash<String> {
public:
  unsigned long operator()(const String &) const;
};

#endif
