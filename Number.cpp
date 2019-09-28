#include "Number.h"

Number::Number() : Number(0) {}

Number::Number(const Number &n) { *this = n; }

bool Number::isIntegral() const { return type == Type_Integral; }

bool Number::isFloatingPoint() const { return type == Type_FloatingPoint; }

Number &Number::operator=(const Number &n) {
  type = n.type;
  if (n.type == Type_FloatingPoint) {
    f = n.f;
  } else {
    i = n.i;
  }
  return *this;
}

Number &Number::operator+=(const Number &n) {
  if (n.isFloatingPoint()) {
    return *this += n.f;
  } else {
    return *this += n.i;
  }
}

Number &Number::operator-=(const Number &n) {
  if (n.isFloatingPoint()) {
    return *this -= n.f;
  } else {
    return *this -= n.i;
  }
}

Number &Number::operator*=(const Number &n) {
  if (n.isFloatingPoint()) {
    return *this *= n.f;
  } else {
    return *this *= n.i;
  }
}

Number &Number::operator/=(const Number &n) {
  if (n.isFloatingPoint()) {
    return *this /= n.f;
  } else {
    return *this /= n.i;
  }
}

Number Number::operator+() const {
  if (isFloatingPoint()) {
    return Number(+f);
  } else {
    return Number(+i);
  }
}

Number Number::operator+(const Number &n) const { return Number(*this) += n; }

Number Number::operator-() const {
  if (isFloatingPoint()) {
    return Number(-f);
  } else {
    return Number(-i);
  }
}

Number Number::operator-(const Number &n) const { return Number(*this) -= n; }

Number Number::operator*(const Number &n) const { return Number(*this) *= n; }

Number Number::operator/(const Number &n) const { return Number(*this) /= n; }

bool Number::operator==(const Number &n) const {
  if (n.isFloatingPoint()) {
    return *this == n.f;
  } else {
    return *this == n.i;
  }
}

bool Number::operator<(const Number &n) const {
  if (n.isFloatingPoint()) {
    return *this < n.f;
  } else {
    return *this < n.i;
  }
}

bool Number::operator>(const Number &n) const {
  if (n.isFloatingPoint()) {
    return *this > n.f;
  } else {
    return *this > n.i;
  }
}

bool Number::operator<=(const Number &n) const {
  if (n.isFloatingPoint()) {
    return *this <= n.f;
  } else {
    return *this <= n.i;
  }
}

bool Number::operator>=(const Number &n) const {
  if (n.isFloatingPoint()) {
    return *this >= n.f;
  } else {
    return *this >= n.i;
  }
}
