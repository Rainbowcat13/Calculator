#ifndef STRING_H
#define STRING_H

#include "Hash.h"
#include <cstddef>

class String {
public:
  String();
  String(char, std::size_t);
  String(const char *);
  String(const String &);
  ~String();
  const char *data() const;
  std::size_t length() const;
  bool isEmpty() const;
  String &operator=(char);
  String &operator=(const char *);
  String &operator=(const String &);
  bool operator==(char) const;
  bool operator==(const char *) const;
  bool operator==(const String &) const;
  char operator[](std::size_t) const;

private:
  std::size_t size;
  char *ptr;
};

template <> class Hash<String> {
public:
  unsigned long operator()(const String &) const;
};

#endif
