#include "Math.h"
#include <cstdint>

const double Math::Epsilon = 1e-9;
const double Math::NotANumber = 0.0 / 0.0;
const double Math::PositiveInfinity = 1.0 / 0.0;
const double Math::NegativeInfinity = -1.0 / 0.0;
const double Math::Pi = 3.14159265358979323846;
const double Math::Euler = 2.71828182845904523536;

double Math::sin(double a) {
  a = reduce2Pi(a);
  double power = a, factorial = 1, result = a, delta = 1;
  int sign = 1;
  for (int i = 3; delta > Epsilon; i += 2) {
    sign = -sign;
    power *= a * a;
    factorial *= (i - 1) * i;
    delta = power / factorial;
    result += sign * delta;
  }
  return result;
}

double Math::cos(double a) {
  a = reduce2Pi(a);
  double power = 1, factorial = 1, result = 1, delta = 1;
  int sign = 1;
  for (int i = 2; delta > Epsilon; i += 2) {
    sign = -sign;
    power *= a * a;
    factorial *= (i - 1) * i;
    delta = power / factorial;
    result += sign * delta;
  }
  return result;
}

double Math::log(double a, double b) {
  if (a <= 0 || b <= 0 || a == 1)
    return NotANumber;
  return log(b) / log(a);
}

double Math::log(double a) {
  if (a <= 0)
    return NotANumber;
  double x0 = a, x1 = x0 - (exp(x0) - a) / exp(x0);
  while (abs(x1 - x0) > 1e-9) {
    x0 = x1;
    x1 = x0 - (exp(x0) - a) / exp(x0);
  }
  return x1;
}

double Math::exp(double a) {
  // TODO: implement better Math::exp(double)
  double res = 1.0;
  for (int i = 13; i > 0; i--) {
    res = 1.0 + a * res / i;
  }
  return res;
}

double Math::pow(double a, double b) {
  // TODO: implement better Math::pow(double, double)
  return exp(log(a) * b);
}

double Math::abs(double a) { return a >= 0 ? a : -a; }

double Math::sqrt(double a) {
  if (a < 0)
    return NotANumber;
  double x0 = a / 2, x1 = x0 - (x0 * x0 - a) / (2 * x0);
  while (abs(x1 - x0) > 1e-9) {
    x0 = x1;
    x1 = x0 - (x0 * x0 - a) / (2 * x0);
  }
  return x1;
}

double Math::cbrt(double a) {
  double x0 = a / 3, x1 = x0 - (x0 * x0 * x0 - a) / (3 * x0 * x0);
  while (abs(x1 - x0) > 1e-9) {
    x0 = x1;
    x1 = x0 - (x0 * x0 * x0 - a) / (3 * x0 * x0);
  }
  return x1;
}

double Math::min(double a, double b) { return a < b ? a : b; }

double Math::max(double a, double b) { return a > b ? a : b; }

double Math::reduce2Pi(double a) {
  if (a < 0) return -reduce2Pi(-a);
  while (a >= 2 * Pi)
    a -= 2 * Pi;
  return a;
}
