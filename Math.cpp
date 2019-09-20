#include "Math.h"

double Math::sin(double a) {
  double power = a, factorial = 1, result = a, delta = 1;
  int sign = 1;
  for (int i = 3; delta > 1e-15; i += 2) {
    sign = -sign;
    power *= a * a;
    factorial *= (i - 1) * i;
    delta = power / factorial;
    result += sign * delta;
  }
  return result;
}

double Math::cos(double a) {
  double power = 1, factorial = 1, result = 1, delta = 1;
  int sign = 1;
  for (int i = 2; delta > 1e-15; i += 2) {
    sign = -sign;
    power *= a * a;
    factorial *= (i - 1) * i;
    delta = power / factorial;
    result += sign * delta;
  }
  return result;
}

double Math::log(double a, double b) {
  return log(b) / log(a);
}

double Math::log(double a) {
  double x0 = a, x1 = x0 - (exp(x0) - a) / exp(x0);
  while (abs(x1 - x0) > 1e-9) {
    x0 = x1;
    x1 = x0 - (exp(x0) - a) / exp(x0);
  }
  return x1;
}

double Math::exp(double a) {
  double res = 1.0;
  for (int i = 1001; i > 0; i--) {
    res = 1.0 + a * res / i;
  }
  return res;
}

double Math::pow(double a, double b) {
  return exp(log(a) * b);
}

double Math::abs(double a) {
  return a >= 0 ? a : -a;
}

double Math::sqrt(double a) {
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

double Math::min(double a, double b) {
  return a < b ? a : b;
}

double Math::max(double a, double b) {
  return a > b ? a : b;
}

