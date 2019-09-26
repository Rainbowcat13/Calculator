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
  std::size_t capacity() const;
  bool isEmpty() const;
  String operator+(char);
  String operator+(const char *);
  String operator+(const String &);
  String &operator+=(char);
  String &operator+=(const char *);
  String &operator+=(const String &);
  String &operator=(char);
  String &operator=(const char *);
  String &operator=(const String &);
  bool operator==(char) const;
  bool operator==(const char *) const;
  bool operator==(const String &) const;
  const char &operator[](std::size_t) const;
  char &operator[](std::size_t);

private:
  static const std::size_t CapacityStep = 10;
  std::size_t size, cap;
  char *ptr;
  void reserve(std::size_t);
  static std::size_t sizeOfPtrString(const char *);
  static void fillPtrString(char *, const char, std::size_t);
  static void copyPtrString(const char *, char *, std::size_t);
};

template <> class Hash<String> {
public:
  unsigned long operator()(const String &) const;
};

#endif
