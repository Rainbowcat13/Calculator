#include "String.h"

String::String(const char *s) {
  if (s[0] == '\0') return;
  for (sz = 1; s[sz] != '\0'; sz++) {}
  ptr = new char[sz];
  for (unsigned int i = 0; i < sz; i++) ptr[i] = s[i];
}

String::String(const String &s) {
  if (s.sz == 0) return;
  sz = s.sz;
  ptr = new char[sz];
  for (unsigned int i = 0; i < sz; i++) ptr[i] = s.ptr[sz];
}

unsigned int String::size() {
  return sz;
}

bool String::isEmpty() {
  return sz == 0;
}

bool String::operator==(const char *s) {
  bool result = true;
  for (unsigned int i = 0; i < sz && s[i] != '\0'; i++) {
    if (ptr[i] != s[i]) {
      result = false;
      break;
    }
  }
  return result;
}

bool String::operator==(const String &s) {
  if (sz != s.sz) return false;
  for (unsigned int i = 0; i < sz; i++) {
    if (ptr[i] != s.ptr[i]) {
      return false;
    }
  }
  return true;
}

char String::operator[](unsigned int i) {
  return ptr[i];
}

