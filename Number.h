#ifndef NUMBER_H
#define NUMBER_H

#include <stdexcept>
#include <string>
#include <type_traits>

class Number {
public:
  using FloatingPoint = double;
  using Integral = long long;
  static const constexpr FloatingPoint Eps = 1e-9;
  static bool isDot(char);
  static bool isExp(char);
  static bool isSign(char);
  static bool isDigit(char);
  static bool isNumber(const std::string &);
  static Number parseNumber(const std::string &);
  Number();
  Number(const Number &);
  bool isInvalid() const;
  bool isIntegral() const;
  bool isFloatingPoint() const;
  Number &operator=(const Number &);
  Number &operator+=(const Number &);
  Number &operator-=(const Number &);
  Number &operator*=(const Number &);
  Number &operator/=(const Number &);
  Number operator+() const;
  Number operator+(const Number &) const;
  Number operator-() const;
  Number operator-(const Number &) const;
  Number operator*(const Number &)const;
  Number operator/(const Number &) const;
  bool operator==(const Number &) const;
  bool operator<(const Number &) const;
  bool operator>(const Number &) const;
  bool operator<=(const Number &) const;
  bool operator>=(const Number &) const;
  template <typename T> explicit Number(const T &);
  template <typename T> explicit operator T() const;
  template <typename T> Number &operator=(const T &);
  template <typename T> Number &operator+=(const T &);
  template <typename T> Number &operator-=(const T &);
  template <typename T> Number &operator*=(const T &);
  template <typename T> Number &operator/=(const T &);
  template <typename T> Number operator+(const T &) const;
  template <typename T> Number operator-(const T &) const;
  template <typename T> Number operator*(const T &)const;
  template <typename T> Number operator/(const T &) const;
  template <typename T> bool operator==(const T &) const;
  template <typename T> bool operator<(const T &) const;
  template <typename T> bool operator>(const T &) const;
  template <typename T> bool operator<=(const T &) const;
  template <typename T> bool operator>=(const T &) const;

private:
  union {
    Integral i;
    FloatingPoint f;
  };
  enum { Type_Integral, Type_FloatingPoint, Type_Invalid } type;
  void checkIntegral();
  void makeIntegral();
  void makeFloatingPoint();
  void makeInvalid();
};

template <typename T> Number::Number(const T &n) { *this = n; }

template <typename T> Number::operator T() const {
  static_assert(std::is_arithmetic<T>::value);
  if (isInvalid()) {
    throw std::logic_error("accesing number that has no value assigned");
  } else if (isFloatingPoint()) {
    return static_cast<T>(f);
  } else {
    return static_cast<T>(i);
  }
}

template <typename T> Number &Number::operator=(const T &n) {
  static_assert(std::is_arithmetic<T>::value);
  if (std::is_floating_point<T>::value) {
    type = Type_FloatingPoint;
    f = static_cast<FloatingPoint>(n);
  } else {
    type = Type_Integral;
    i = static_cast<Integral>(n);
  }
  checkIntegral();
  return *this;
}

template <typename T> Number &Number::operator+=(const T &n) {
  static_assert(std::is_arithmetic<T>::value);
  if (isInvalid()) {
    return *this;
  } else if (isFloatingPoint()) {
    f += static_cast<FloatingPoint>(n);
  } else if (std::is_floating_point<T>::value) {
    type = Type_FloatingPoint;
    f = static_cast<FloatingPoint>(i) + static_cast<FloatingPoint>(n);
  } else {
    i += static_cast<Integral>(n);
  }
  checkIntegral();
  return *this;
}

template <typename T> Number &Number::operator-=(const T &n) {
  static_assert(std::is_arithmetic<T>::value);
  if (isInvalid()) {
    return *this;
  } else if (isFloatingPoint()) {
    f -= static_cast<FloatingPoint>(n);
  } else if (std::is_floating_point<T>::value) {
    type = Type_FloatingPoint;
    f = static_cast<FloatingPoint>(i) - static_cast<FloatingPoint>(n);
  } else {
    i -= static_cast<Integral>(n);
  }
  checkIntegral();
  return *this;
}

template <typename T> Number &Number::operator*=(const T &n) {
  static_assert(std::is_arithmetic<T>::value);
  if (isInvalid()) {
    return *this;
  } else if (isFloatingPoint()) {
    f *= static_cast<FloatingPoint>(n);
  } else if (std::is_floating_point<T>::value) {
    type = Type_FloatingPoint;
    f = static_cast<FloatingPoint>(i) * static_cast<FloatingPoint>(n);
  } else {
    i *= static_cast<Integral>(n);
  }
  checkIntegral();
  return *this;
}

template <typename T> Number &Number::operator/=(const T &n) {
  static_assert(std::is_arithmetic<T>::value);
  if (n == 0) {
    throw std::invalid_argument("division by zero");
  } else if (isInvalid()) {
    return *this;
  } else if (isFloatingPoint()) {
    f /= static_cast<FloatingPoint>(n);
  } else {
    type = Type_FloatingPoint;
    f = static_cast<FloatingPoint>(i) / static_cast<FloatingPoint>(n);
  }
  checkIntegral();
  return *this;
}

template <typename T> Number Number::operator+(const T &n) const {
  return Number(*this) += n;
}

template <typename T> Number Number::operator-(const T &n) const {
  return Number(*this) -= n;
}

template <typename T> Number Number::operator*(const T &n) const {
  return Number(*this) *= n;
}

template <typename T> Number Number::operator/(const T &n) const {
  return Number(*this) /= n;
}

template <typename T> bool Number::operator==(const T &n) const {
  static_assert(std::is_arithmetic<T>::value);
  if (isInvalid()) {
    return false;
  } else if (isFloatingPoint()) {
    return f == static_cast<FloatingPoint>(n);
  } else if (std::is_floating_point<T>::value) {
    return static_cast<FloatingPoint>(i) == static_cast<FloatingPoint>(n);
  } else {
    return i == static_cast<Integral>(n);
  }
}

template <typename T> bool Number::operator<(const T &n) const {
  static_assert(std::is_arithmetic<T>::value);
  if (isInvalid()) {
    return false;
  } else if (isFloatingPoint()) {
    return f < static_cast<FloatingPoint>(n);
  } else if (std::is_floating_point<T>::value) {
    return static_cast<FloatingPoint>(i) < static_cast<FloatingPoint>(n);
  } else {
    return i < static_cast<Integral>(n);
  }
}

template <typename T> bool Number::operator>(const T &n) const {
  static_assert(std::is_arithmetic<T>::value);
  if (isInvalid()) {
    return false;
  } else if (isFloatingPoint()) {
    return f > static_cast<FloatingPoint>(n);
  } else if (std::is_floating_point<T>::value) {
    return static_cast<FloatingPoint>(i) > static_cast<FloatingPoint>(n);
  } else {
    return i > static_cast<Integral>(n);
  }
}

template <typename T> bool Number::operator<=(const T &n) const {
  static_assert(std::is_arithmetic<T>::value);
  if (isInvalid()) {
    return false;
  } else if (isFloatingPoint()) {
    return f <= static_cast<FloatingPoint>(n);
  } else if (std::is_floating_point<T>::value) {
    return static_cast<FloatingPoint>(i) <= static_cast<FloatingPoint>(n);
  } else {
    return i <= static_cast<Integral>(n);
  }
}

template <typename T> bool Number::operator>=(const T &n) const {
  static_assert(std::is_arithmetic<T>::value);
  if (isInvalid()) {
    return false;
  } else if (isFloatingPoint()) {
    return f >= static_cast<FloatingPoint>(n);
  } else if (std::is_floating_point<T>::value) {
    return static_cast<FloatingPoint>(i) >= static_cast<FloatingPoint>(n);
  } else {
    return i >= static_cast<Integral>(n);
  }
}

#endif
