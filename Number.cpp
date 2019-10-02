#include "Number.h"
#include <stdexcept>

bool Number::isNumber(const std::string &s) {
  if (s.empty())
    return false;
  int n = s.length(), numSignPos = -1, dotPos = -1, expPos = -1;
  for (int i = 0; i < n; i++) {
    if (s[i] == '.' && i != n - 1 && i > 0 && expPos == -1 && dotPos == -1 &&
        numSignPos != i - 1) {
      dotPos = i;
    } else if (s[i] == 'e' && i != n - 1 && i > 0 && expPos == -1 &&
               dotPos != i - 1 && numSignPos != i - 1) {
      expPos = i;
    } else if ((s[i] == '-' || s[i] == '+') && i != n - 1 && i == 0) {
      numSignPos = i;
    } else if ((s[i] == '-' || s[i] == '+') && i != n - 1 && i > 0 &&
               expPos == i - 1) {
      continue;
    } else if (s[i] >= '0' && s[i] <= '9') {
      continue;
    } else {
      return false;
    }
  }
  return true;
}

Number Number::parseNumber(const std::string &s) {
  if (s.empty())
    throw std::invalid_argument("not a number: " + s);
  bool numSign = true, expSign = true;
  int n = s.length(), numSignPos = -1, fracEndPos = -1, dotPos = -1,
      expPos = -1;
  Number::Integral num = 0, exp = 0, mul = 1;
  for (int i = 0; i < n; i++) {
    if (s[i] == '.' && i != n - 1 && i > 0 && expPos == -1 && dotPos == -1 &&
        numSignPos != i - 1) {
      dotPos = i;
    } else if (s[i] == 'e' && i != n - 1 && i > 0 && expPos == -1 &&
               dotPos != i - 1 && numSignPos != i - 1) {
      expPos = i;
    } else if ((s[i] == '-' || s[i] == '+') && i != n - 1 && i == 0) {
      numSignPos = i;
      numSign = (s[i] == '+');
    } else if ((s[i] == '-' || s[i] == '+') && i != n - 1 && i > 0 &&
               expPos == i - 1) {
      expSign = (s[i] == '+');
    } else if (s[i] >= '0' && s[i] <= '9') {
      if (expPos != -1 && i > expPos) {
        exp = exp * 10 + s[i] - '0';
      } else if (dotPos != -1 && i > dotPos) {
        num = num * 10 + s[i] - '0';
        fracEndPos = i;
      } else {
        num = num * 10 + s[i] - '0';
      }
    } else {
      throw std::invalid_argument("not a number: " + s);
    }
  }
  if (!numSign)
    num = -num;
  if (expSign)
    exp -= fracEndPos - dotPos;
  else
    exp += fracEndPos - dotPos;
  if (exp < 0) {
    exp = -exp;
    expSign = !expSign;
  }
  mul <<= exp;
  while (exp--)
    mul += mul << 2;
  if (expSign)
    return Number(num * mul);
  else
    return Number(static_cast<FloatingPoint>(num) / mul);
}

Number::Number() { makeInvalid(); }

Number::Number(const Number &n) { *this = n; }

bool Number::isInvalid() const { return type == Type_Invalid; }

bool Number::isIntegral() const { return type == Type_Integral; }

bool Number::isFloatingPoint() const { return type == Type_FloatingPoint; }

Number &Number::operator=(const Number &n) {
  if (n.isInvalid()) {
    makeInvalid();
    return *this;
  } else if (n.isFloatingPoint()) {
    return *this = n.f;
  } else {
    return *this = n.i;
  }
}

Number &Number::operator+=(const Number &n) {
  if (n.isInvalid()) {
    makeInvalid();
    return *this;
  } else if (n.isFloatingPoint()) {
    return *this += n.f;
  } else {
    return *this += n.i;
  }
}

Number &Number::operator-=(const Number &n) {
  if (n.isInvalid()) {
    makeInvalid();
    return *this;
  } else if (n.isFloatingPoint()) {
    return *this -= n.f;
  } else {
    return *this -= n.i;
  }
}

Number &Number::operator*=(const Number &n) {
  if (n.isInvalid()) {
    makeInvalid();
    return *this;
  } else if (n.isFloatingPoint()) {
    return *this *= n.f;
  } else {
    return *this *= n.i;
  }
}

Number &Number::operator/=(const Number &n) {
  if (n.isInvalid()) {
    makeInvalid();
    return *this;
  } else if (n.isFloatingPoint()) {
    return *this /= n.f;
  } else {
    return *this /= n.i;
  }
}

Number Number::operator+() const {
  if (isInvalid()) {
    return Number();
  }
  if (isFloatingPoint()) {
    return Number(+f);
  } else {
    return Number(+i);
  }
}

Number Number::operator+(const Number &n) const { return Number(*this) += n; }

Number Number::operator-() const {
  if (isInvalid()) {
    return Number();
  } else if (isFloatingPoint()) {
    return Number(-f);
  } else {
    return Number(-i);
  }
}

Number Number::operator-(const Number &n) const { return Number(*this) -= n; }

Number Number::operator*(const Number &n) const { return Number(*this) *= n; }

Number Number::operator/(const Number &n) const { return Number(*this) /= n; }

bool Number::operator==(const Number &n) const {
  if (n.isInvalid()) {
    return false;
  } else if (n.isFloatingPoint()) {
    return *this == n.f;
  } else {
    return *this == n.i;
  }
}

bool Number::operator<(const Number &n) const {
  if (n.isInvalid()) {
    return false;
  } else if (n.isFloatingPoint()) {
    return *this < n.f;
  } else {
    return *this < n.i;
  }
}

bool Number::operator>(const Number &n) const {
  if (n.isInvalid()) {
    return false;
  } else if (n.isFloatingPoint()) {
    return *this > n.f;
  } else {
    return *this > n.i;
  }
}

bool Number::operator<=(const Number &n) const {
  if (n.isInvalid()) {
    return false;
  } else if (n.isFloatingPoint()) {
    return *this <= n.f;
  } else {
    return *this <= n.i;
  }
}

bool Number::operator>=(const Number &n) const {
  if (n.isInvalid()) {
    return false;
  } else if (n.isFloatingPoint()) {
    return *this >= n.f;
  } else {
    return *this >= n.i;
  }
}

void Number::checkIntegral() {
  struct {
    FloatingPoint operator()(FloatingPoint a) { return a >= 0 ? a : -a; }
  } abs;
  if (isFloatingPoint() && abs(f - static_cast<Integral>(f)) < Eps)
    makeIntegral();
}

void Number::makeInvalid() {
  i = 0;
  type = Type_Invalid;
}

void Number::makeIntegral() { *this = static_cast<Integral>(*this); }

void Number::makeFloatingPoint() { *this = static_cast<FloatingPoint>(*this); }
