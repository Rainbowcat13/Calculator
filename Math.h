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
Number pow(const Number &, const Number &);
Number exp(const Number &);
Number abs(const Number &);
Number sqrt(const Number &);
Number cbrt(const Number &);
Number min(const Number &, const Number &);
Number max(const Number &, const Number &);
} // namespace Math

#endif
