#ifndef MyString_H
#define MyString_H

#include "Hash.h"
#include <cstddef>

class MyString {
public:
  MyString();
  MyString(char, std::size_t);
  MyString(const char *);
  MyString(const MyString &);
  ~MyString();
  const char *data() const;
  std::size_t length() const;
  bool isEmpty() const;
  MyString &operator=(char);
  MyString &operator=(const char *);
  MyString &operator=(const MyString &);
  bool operator==(char) const;
  bool operator==(const char *) const;
  bool operator==(const MyString &) const;
  char operator[](std::size_t) const;

private:
  std::size_t size;
  char *ptr;
};

template <> class Hash<MyString> {
public:
  unsigned long operator()(const MyString &) const;
};

#endif
