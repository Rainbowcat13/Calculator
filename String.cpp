#include "String.h"
#include <stdexcept>

String::String() {
  size = cap = 0;
  ptr = nullptr;
  reserve(0);
  fillPtrString(ptr, '\0', 0);
}

String::String(char c, std::size_t n) {
  size = cap = 0;
  ptr = nullptr;
  reserve(n);
  fillPtrString(ptr, c, n);
}

String::String(const char *s) {
  size = cap = 0;
  ptr = nullptr;
  std::size_t n = sizeOfPtrString(s);
  reserve(n);
  copyPtrString(s, ptr, n);
}

String::String(const String &s) {
  size = cap = 0;
  ptr = nullptr;
  reserve(s.size);
  copyPtrString(s.ptr, ptr, s.size);
}

String::~String() { delete[] ptr; }

const char *String::data() const { return ptr; }

std::size_t String::length() const { return size; }

std::size_t String::capacity() const { return cap; }

bool String::isEmpty() const { return size == 0; }

String String::operator+(char c) {
  return String(*this) += c;
}

String String::operator+(const char *s) {
  return String(*this) += s;
}

String String::operator+(const String &s) {
  return String(*this) += s;
}

String &String::operator+=(char c) {
  reserve(size + 1);
  fillPtrString(ptr + size - 1, c, 1);
  return *this;
}

String &String::operator+=(const char *s) {
  std::size_t n = sizeOfPtrString(s);
  reserve(size + n);
  copyPtrString(s, ptr + (size - n), n);
  return *this;
}

String &String::operator+=(const String &s) {
  reserve(size + s.size);
  copyPtrString(s.ptr, ptr + (size - s.size), s.size);
  return *this;
}

String &String::operator=(char c) {
  reserve(1);
  fillPtrString(ptr, c, 1);
  return *this;
}

String &String::operator=(const char *s) {
  std::size_t n = sizeOfPtrString(s);
  reserve(n);
  copyPtrString(s, ptr, n);
  return *this;
}

String &String::operator=(const String &s) {
  reserve(s.size);
  copyPtrString(s.ptr, ptr, s.size);
  return *this;
}

bool String::operator==(char c) const { return size == 1 && ptr[0] == c; }

bool String::operator==(const char *s) const {
  std::size_t i;
  for (i = 0; i < size; i++)
    if (s[i] == '\0' || s[i] != ptr[i])
      return false;
  return s[i] == '\0';
}

bool String::operator==(const String &s) const {
  if (size != s.size)
    return false;
  for (std::size_t i = 0; i < size; i++)
    if (ptr[i] != s.ptr[i])
      return false;
  return true;
}

const char &String::operator[](std::size_t i) const {
  if (i > size) throw std::out_of_range("invalid index");
  return ptr[i];
}

char &String::operator[](std::size_t i) {
  if (i > size) throw std::out_of_range("invalid index");
  return ptr[i];
}

void String::reserve(std::size_t n) {
  std::size_t oldSize = size;
  size = n;
  if (ptr != nullptr && size <= cap)
    return;
  if (size == 0)
    cap = CapacityStep;
  else
    cap = ((size - 1) / CapacityStep + 1) * CapacityStep;
  char *newPtr = new char[cap + 1];
  if (ptr != nullptr)
    copyPtrString(ptr, newPtr, oldSize);
  delete[] ptr;
  ptr = newPtr;
}

std::size_t String::sizeOfPtrString(const char *s) {
  std::size_t l = 0;
  while (*(s++))
    l++;
  return l;
}

void String::fillPtrString(char *s, const char c, std::size_t n) {
  s[n] = '\0';
  for (std::size_t i = 0; i < n; i++)
    s[i] = c;
}

void String::copyPtrString(const char *src, char *dest, std::size_t n) {
  dest[n] = '\0';
  for (std::size_t i = 0; i < n; i++)
    dest[i] = src[i];
}

unsigned long Hash<String>::operator()(const String &s) const {
  const unsigned long p = 293, mod = static_cast<int>(1e9) + 7;
  unsigned long hashValue = 0, pow = 1;
  for (std::size_t i = 0; i < s.length(); i++) {
    hashValue = (hashValue + s[i] * pow) % mod;
    pow = (pow * p) % mod;
  }
  return hashValue;
}
