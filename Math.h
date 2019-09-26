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