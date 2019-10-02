#include "Math.h"
#include <cmath>

Number Math::pi() { return Number(3.14159265358979323846); }

Number Math::euler() { return Number(2.71828182845904523536); }

Number Math::sin(const Number &a) {
  if (a < 0)
    return -sin(-a);
  Number::FloatingPoint n = static_cast<Number::FloatingPoint>(a);
  n = std::fmod(n, static_cast<Number::FloatingPoint>(pi()) * 2);
  Number::FloatingPoint p = n, f = 1, r = n, d = 1;
  char s = 1;
  for (int i = 3; d > Number::Eps; i += 2) {
    s = -s;
    p *= n * n;
    f *= (i - 1) * i;
    d = p / f;
    r += s * d;
  }
  return Number(r);
}

Number Math::cos(const Number &a) {
  if (a < 0)
    return cos(-a);
  Number::FloatingPoint n = static_cast<Number::FloatingPoint>(a);
  n = std::fmod(n, static_cast<Number::FloatingPoint>(pi()) * 2);
  Number::FloatingPoint p = 1, f = 1, r = 1, d = 1;
  char s = 1;
  for (int i = 2; d > Number::Eps; i += 2) {
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
  // TODO: use log2 and exp2 instead
  return log(b) / log(a);
}

Number Math::log(const Number &a) {
  if (a <= 0)
    throw std::invalid_argument("logarithm of negative number");
  // TODO: reimplement logarithm
  struct {
    Number::FloatingPoint operator()(Number::FloatingPoint n) {
      Number::FloatingPoint res = 1.0;
      for (int i = 13; i > 0; i--)
        res = 1.0 + n * res / i;
      return res;
    }
  } e;
  Number::FloatingPoint n = static_cast<Number::FloatingPoint>(a);
  Number::FloatingPoint x0 = n / 2, x = x0 - (e(x0) - n) / (e(x0));
  while (x - x0 > Number::Eps || x - x0 < -Number::Eps) {
    x0 = x;
    x = x0 - (e(x0) - n) / (e(x0));
  }
  return Number(x);
}

Number Math::log2(const Number &a) {
  if (a <= 0)
    throw std::invalid_argument("logarithm of negative number");
  // TODO: implement logarithm
  throw std::logic_error("binary logarithm is not implemented");
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
    // TODO: use exp2 and log2 instead
    return exp(log(a) * b);
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
  throw std::logic_error("binary exponentiation is not implemented");
}

Number Math::abs(const Number &a) { return a >= 0 ? +a : -a; }

Number Math::sqrt(const Number &a) {
  if (a <= 0)
    throw std::invalid_argument("square root of negative number");
  Number::FloatingPoint n = static_cast<Number::FloatingPoint>(a);
  Number::FloatingPoint x0 = n / 2, x = x0 - (x0 * x0 - n) / (2 * x0);
  while (x - x0 > Number::Eps || x - x0 < -Number::Eps) {
    x0 = x;
    x = x0 - (x0 * x0 - n) / (2 * x0);
  }
  return Number(x);
}

Number Math::cbrt(const Number &a) {
  Number::FloatingPoint n = static_cast<Number::FloatingPoint>(a);
  Number::FloatingPoint x0 = n / 3, x = x0 - (x0 * x0 * x0 - n) / (3 * x0 * x0);
  while (x - x0 > Number::Eps || x - x0 < -Number::Eps) {
    x0 = x;
    x = x0 - (x0 * x0 * x0 - n) / (3 * x0 * x0);
  }
  return Number(x);
}

Number Math::min(const Number &a, const Number &b) { return a < b ? a : b; }

Number Math::max(const Number &a, const Number &b) { return a > b ? a : b; }
