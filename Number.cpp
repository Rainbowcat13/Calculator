#include "Number.h"
#include <stdexcept>

bool Number::isDot(char c) { return c == '.'; }

bool Number::isDigit(char c) { return c >= '0' && c <= '9'; }

bool Number::isSign(char c) { return c == '+' || c == '-'; }

bool Number::isExp(char c) { return c == 'e' || c == 'E'; }

bool Number::isNumber(const std::string &s) {
  int n = s.length(), sn = -1, d = -1, se = -1, e = -1;
  for (int i = 0; i < n; i++)
    if (isDot(s[i]) && i > 0 && e < 0 && d < 0 && sn != i - 1)
      d = i;
    else if (isExp(s[i]) && i > 0 && e < 0 && d != i - 1 && sn != i - 1)
      e = i;
    else if (isSign(s[i]) && i == 0)
      sn = i;
    else if (isSign(s[i]) && i == e + 1)
      se = i;
    else if (isDigit(s[i]))
      continue;
    else
      return false;
  return d != n - 1 && e != n - 1 && sn != n - 1 && se != n - 1;
}

Number Number::parseNumber(const std::string &s) {
  if (s.empty())
    throw std::invalid_argument("not a number: " + s);
  bool nums = true, exps = true;
  int n = s.length(), sn = -1, d = -1, se = -1, e = -1, fe = -1;
  Integral num = 0, exp = 0, mul = 1;
  for (int i = 0; i < n; i++) {
    if (isDot(s[i]) && i > 0 && e < 0 && d < 0 && sn != i - 1) {
      d = i;
    } else if (isExp(s[i]) && i > 0 && e < 0 && d != i - 1 && sn != i - 1) {
      e = i;
    } else if (isSign(s[i]) && i == 0) {
      sn = i;
      nums = (s[i] == '+');
    } else if (isSign(s[i]) && i == e + 1) {
      se = i;
      exps = (s[i] == '+');
    } else if (isDigit(s[i])) {
      if (e > 0 && i > e) {
        exp = exp * 10 + s[i] - '0';
      } else if (d > 0 && i > d) {
        num = num * 10 + s[i] - '0';
        fe = i;
      } else {
        num = num * 10 + s[i] - '0';
      }
    } else {
      throw std::invalid_argument("not a number: " + s);
    }
  }
  if (sn == n - 1 || d == n - 1 || se == n - 1 || e == n - 1)
    throw std::invalid_argument("not a number: " + s);
  if (!nums)
    num = -num;
  if (exps)
    exp -= fe - d;
  else
    exp += fe - d;
  if (exp < 0) {
    exp = -exp;
    exps = !exp;
  }
  mul <<= exp;
  while (exp--)
    mul += mul << 2;
  if (exps)
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
