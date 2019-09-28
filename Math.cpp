#include "Math.h"

Number Math::pi() { return Number(3.14159265358979323846); }

Number Math::euler() { return Number(2.71828182845904523536); }

Number Math::sin(const Number &a) {
  Number::FloatingPoint n = static_cast<Number::FloatingPoint>(a);
  Number::FloatingPoint p = n, f = 1, r = n, d = 1;
  char s = 1;
  for (int i = 3; d > 1e-9; i += 2) {
    s = -s;
    p *= n * n;
    f *= (i - 1) * i;
    d = p / f;
    r += s * d;
  }
  return Number(r);
}

Number Math::cos(const Number &a) {
  Number::FloatingPoint n = static_cast<Number::FloatingPoint>(a);
  Number::FloatingPoint p = 1, f = 1, r = 1, d = 1;
  char s = 1;
  for (int i = 2; d > 1e-9; i += 2) {
    s = -s;
    p *= n * n;
    f *= (i - 1) * i;
    d = p / f;
    r += s * d;
  }
  return Number(r);
}

Number Math::log(const Number &a, const Number &b) {
  if (a <= 0)
    throw std::invalid_argument("logarithm with negative base");
  if (a == 1)
    throw std::invalid_argument("logarithm with base = 1");
  if (b <= 0)
    throw std::invalid_argument("logarithm of negative number");
  return log2(b) / log2(a);
}

Number Math::log(const Number &a) {
  if (a <= 0)
    throw std::invalid_argument("logarithm of negative number");
  // TODO: implement logarithm
  return Number(0.0);
}

Number Math::log2(const Number &a) {
  if (a <= 0)
    throw std::invalid_argument("logarithm of negative number");
  // TODO: implement logarithm
  return Number(0.0);
}

Number Math::pow(const Number &a, const Number &b) {
  if (b < 0) {
    if (a == 0)
      throw std::invalid_argument("zero power with negative exponent");
    return Number(1.0 / static_cast<Number::FloatingPoint>(pow(a, -b)));
  } else if (b == 0) {
    return Number(1);
  } else if (b.isFloatingPoint()) {
    if (a <= 0)
      throw std::invalid_argument("floating-point power with negative base");
    return exp2(log2(a) * b);
  } else if (a.isFloatingPoint()) {
    Number::Integral p = static_cast<Number::Integral>(b);
    Number::FloatingPoint n = static_cast<Number::FloatingPoint>(a);
    Number::FloatingPoint res = 1;
    while (p > 0) {
      if (p % 2 == 1)
        res *= n;
      n *= n;
      p /= 2;
    }
    return Number(res);
  } else {
    Number::Integral p = static_cast<Number::Integral>(b);
    Number::Integral n = static_cast<Number::FloatingPoint>(a);
    Number::Integral res = 1;
    while (p > 0) {
      if (p % 2 == 1)
        res *= n;
      n *= n;
      p /= 2;
    }
    return Number(res);
  }
}

Number Math::exp(const Number &a) {
  Number::FloatingPoint n = static_cast<Number::FloatingPoint>(a);
  Number::FloatingPoint res = 1.0;
  for (int i = 13; i > 0; i--)
    res = 1.0 + n * res / i;
  return Number(res);
}

Number Math::exp2(const Number &a) {
  // TODO: implement exponentiation
  return Number(0.0);
}

Number Math::abs(const Number &a) { return a >= 0 ? +a : -a; }

Number Math::sqrt(const Number &a) {
  if (a <= 0)
    throw std::invalid_argument("square root of negative number");
  Number::FloatingPoint n = static_cast<Number::FloatingPoint>(a);
  Number::FloatingPoint x0 = n / 2, x = x0 - (x0 * x0 - n) / (2 * x0);
  while (x - x0 > 1e-9 || x - x0 < -1e-9) {
    x0 = x;
    x = x0 - (x0 * x0 - n) / (2 * x0);
  }
  return Number(x);
}

Number Math::cbrt(const Number &a) {
  Number::FloatingPoint n = static_cast<Number::FloatingPoint>(a);
  Number::FloatingPoint x0 = n / 3, x = x0 - (x0 * x0 * x0 - n) / (3 * x0 * x0);
  while (x - x0 > 1e-9 || x - x0 < -1e-9) {
    x0 = x;
    x = x0 - (x0 * x0 * x0 - n) / (3 * x0 * x0);
  }
  return Number(x);
}

Number Math::min(const Number &a, const Number &b) { return a < b ? a : b; }

Number Math::max(const Number &a, const Number &b) { return a > b ? a : b; }
