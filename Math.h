<<<<<<< HEAD
#ifndef MATH_H
#define MATH_H

class Math {
public:
  static const double Epsilon;
  static const double NotANumber;
  static const double PositiveInfinity;
  static const double NegativeInfinity;
  static const double Pi;
  static const double Euler;
  static double sin(double);
  static double cos(double);
  static double log(double, double);
  static double log(double);
  static double exp(double);
  static double pow(double, double);
  static double abs(double);
  static double sqrt(double);
  static double cbrt(double);
  static double min(double, double);
  static double max(double, double);

private:
  static double reduce2Pi(double);
};

#endif
=======
#ifndef MATH_H
#define MATH_H

#include "Number.h"

namespace Math {
Number pi();
Number euler();
Number sin(const Number &);
Number cos(const Number &);
Number log(const Number &, const Number &);
Number log(const Number &);
Number log2(const Number &);
Number pow(const Number &, const Number &);
Number exp(const Number &);
Number exp2(const Number &);
Number abs(const Number &);
Number sqrt(const Number &);
Number cbrt(const Number &);
Number min(const Number &, const Number &);
Number max(const Number &, const Number &);
} // namespace Math

#endif
>>>>>>> cc4f7a71590d8d6f35516dc65ef1573b9b2a42e3
