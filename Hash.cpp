#include "Hash.h"

unsigned long Hash<std::string>::operator()(const std::string &s) const {
  const unsigned long p = 293, mod = static_cast<int>(1e9) + 7;
  unsigned long hashValue = 0, pow = 1;
  for (std::size_t i = 0; i < s.length(); i++) {
    hashValue = (hashValue + s[i] * pow) % mod;
    pow = (pow * p) % mod;
  }
  return hashValue;
}
