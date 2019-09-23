#include "String.h"

String::String(const char *s) {
  for (size = 0; s[size] != '\0'; size++) {
  }
  ptr = new char[size + 1];
  for (unsigned int i = 0; i <= size; i++)
    ptr[i] = s[i];
}

String::String(const String &s) {
  size = s.size;
  ptr = new char[size + 1];
  for (unsigned int i = 0; i <= size; i++)
    ptr[i] = s.ptr[i];
}

String::~String() {
  // delete[] ptr;
}

const char *String::data() const { return ptr; }

unsigned int String::length() const { return size; }

bool String::isEmpty() const { return size == 0; }

bool String::operator==(const char *s) const {
  unsigned int i;
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
  for (unsigned int i = 0; i < size; i++) {
    if (ptr[i] != s.ptr[i]) {
      return false;
    }
  }
  return true;
}

char String::operator[](unsigned int i) const { return ptr[i]; }

unsigned long Hash<String>::operator()(const String &s) const {
  const int p = 31, mod = static_cast<int>(1e9) + 7;
  long long hashValue = 0, pow = 1;
  for (unsigned int i = 0; i < s.length(); i++) {
    hashValue = (hashValue + s[i] * pow) % mod;
    pow = (pow * p) % mod;
  }
  return hashValue;
}
