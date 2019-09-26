#include "String.h"

String::String() {
  ptr = new char[1]{'\0'};
  size = 0;
}

String::String(char c, std::size_t n) {
  ptr = new char[n + 1];
  size = n;
  ptr[n] = '\0';
  for (std::size_t i = 0; i < n; i++)
    ptr[i] = c;
}

String::String(const char *s) {
  size = 0;
  while (s[size] != '\0')
    size++;
  ptr = new char[size + 1];
  for (std::size_t i = 0; i <= size; i++)
    ptr[i] = s[i];
}

String::String(const String &s) {
  size = s.size;
  ptr = new char[size + 1];
  for (std::size_t i = 0; i <= size; i++)
    ptr[i] = s.ptr[i];
}

String::~String() { delete[] ptr; }

const char *String::data() const { return ptr; }

std::size_t String::length() const { return size; }

bool String::isEmpty() const { return size == 0; }

String &String::operator=(char c) {
  delete[] ptr;
  ptr = new char[2]{c, '\0'};
  size = 1;
  return *this;
}

String &String::operator=(const char *s) {
  delete[] ptr;
  size = 0;
  while (s[size] != '\0')
    size++;
  ptr = new char[size + 1];
  for (std::size_t i = 0; i <= size; i++)
    ptr[i] = s[i];
  return *this;
}

String &String::operator=(const String &s) {
  delete[] ptr;
  ptr = new char[s.size + 1];
  size = s.size;
  for (std::size_t i = 0; i <= size; i++)
    ptr[i] = s.ptr[i];
  return *this;
}

bool String::operator==(char c) const { return size == 1 && ptr[0] == c; }

bool String::operator==(const char *s) const {
  std::size_t i;
  for (i = 0; i < size; i++) {
    if (s[i] == '\0' || s[i] != ptr[i]) {
      return false;
    }
  }
  return s[i] == '\0';
}

bool String::operator==(const String &s) const {
  if (size != s.size)
    return false;
  for (std::size_t i = 0; i < size; i++) {
    if (ptr[i] != s.ptr[i]) {
      return false;
    }
  }
  return true;
}

char String::operator[](std::size_t i) const { return ptr[i]; }

unsigned long Hash<String>::operator()(const String &s) const {
  const unsigned long p = 293, mod = static_cast<int>(1e9) + 7;
  unsigned long hashValue = 0, pow = 1;
  for (std::size_t i = 0; i < s.length(); i++) {
    hashValue = (hashValue + s[i] * pow) % mod;
    pow = (pow * p) % mod;
  }
  return hashValue;
}
