#include "expression.h"
#include "math.h"
#include "Stack.h"
#include <stdexcept>

Expression::Expression(Queue<MyString> q) {
  Stack<MyString> s;
  s.push(MyString("("));
  q.push(MyString(")"));
  bool possibleNegation = true, requireFnBraces = false;
  while (!q.isEmpty()) {
    if (s.isEmpty())
      failMissingLeftBrace();
    MyString v = q.pop();
    if (v == "-" && possibleNegation)
      v = "~";
    if (isNumber(v) || isConstant(v)) {
      postfix.push(v);
      possibleNegation = false;
    } else if (isVariable(v)) {
      variables[v] = 0;
      postfix.push(v);
      possibleNegation = false;
    } else if (isUnaryOperator(v)) {
      s.push(v);
      possibleNegation = false;
    } else if (isFunction(v)) {
      s.push(v);
      possibleNegation = false;
      requireFnBraces = true;
    } else if (isBinaryOperator(v)) {
      if (associativity(v) == Associativity_Right) {
        while (precedence(v) < precedence(s.top())) {
          postfix.push(s.pop());
        }
      } else if (associativity(v) == Associativity_Left) {
        while (precedence(v) <= precedence(s.top())) {
          postfix.push(s.pop());
        }
      } else {
        failWrongAssociativity(v);
      }
      s.push(v);
      possibleNegation = true;
    } else if (isLeftBrace(v)) {
      if (requireFnBraces && braceType(v) != BraceType_Round)
        failWrongBraceType(v);
      s.push(v);
      possibleNegation = true;
      requireFnBraces = false;
    } else if (isRightBrace(v)) {
      while (!isLeftBrace(s.top())) {
        postfix.push(s.pop());
      }
      if (braceType(v) != braceType(s.top()))
        failWrongBraceType(v);
      s.pop();
      possibleNegation = false;
    } else if (isComma(v)) {
      while (!isLeftBrace(s.top())) {
        postfix.push(s.pop());
      }
      possibleNegation = true;
    } else {
      failWrongToken(v);
    }
  }
  if (!s.isEmpty())
    failMissingRightBrace();
}

Expression::Expression(const Expression &e) { postfix = e.postfix; }

Expression::ResultType Expression::evaluate() const {
  if (postfix.isEmpty())
    return 0;
  Queue<MyString> q = postfix;
  Stack<ResultType> s;
  while (!q.isEmpty()) {
    MyString v = q.pop();
    if (isNumber(v)) {
      s.push(parseNumber(v));
    } else if (isConstant(v)) {
      s.push(getConstant(v));
    } else if (isVariable(v)) {
      s.push(getVariable(v));
    } else if (isBinaryOperator(v) || isBinaryFunction(v)) {
      if (s.isEmpty())
        failMissingOperand();
      ResultType b = s.pop();
      if (s.isEmpty())
        failMissingOperand();
      ResultType a = s.pop();
      s.push(doBinaryOperation(v, a, b));
    } else if (isUnaryOperator(v) || isUnaryFunction(v)) {
      if (s.isEmpty())
        failMissingOperand();
      ResultType a = s.pop();
      s.push(doUnaryOperation(v, a));
    } else {
      failWrongToken(v);
    }
  }
  ResultType res = s.pop();
  if (!s.isEmpty())
    failMissingOperator();
  return res;
}

Queue<MyString> Expression::getPostfix() const { return postfix; }

List<MyString> Expression::getVariablesNames() const { return variables.keys(); }

Expression::ResultType Expression::getVariable(MyString &s) const {
  return variables[s];
}

void Expression::setVariable(MyString &s, Expression::ResultType value) {
  variables[s] = value;
}

bool Expression::isNumber(const MyString &s) {
  bool dot = false, exp = false;
  for (std::size_t i = 0; i < s.length(); i++) {
    if (i > 0 && !exp && !dot && s[i] == '.') {
      dot = true;
    } else if (i > 0 && !exp && s[i] == 'e') {
      exp = true;
    } else if (i == 0 && s[i] == '-') {
      continue;
    } else if (i > 0 && s[i - 1] == 'e' && (s[i] == '-' || s[i] == '+')) {
      continue;
    } else if (s[i] >= '0' && s[i] <= '9') {
      continue;
    } else {
      return false;
    }
  }
  return true;
}

bool Expression::isOperator(const MyString &s) {
  return isUnaryOperator(s) || isBinaryOperator(s);
}

bool Expression::isUnaryOperator(const MyString &s) { return s == "~"; }

bool Expression::isBinaryOperator(const MyString &s) {
  return s == "+" || s == "-" || s == "*" || s == "/" || s == "^";
}

bool Expression::isFunction(const MyString &s) {
  return isUnaryFunction(s) || isBinaryFunction(s);
}

bool Expression::isUnaryFunction(const MyString &s) {
  return s == "sin" || s == "cos" || s == "exp" || s == "abs" || s == "sqrt" ||
         s == "cbrt";
}

bool Expression::isBinaryFunction(const MyString &s) {
  return s == "pow" || s == "log" || s == "min" || s == "max";
}

bool Expression::isConstant(const MyString &s) {
  return s == "e" || s == "pi" || s == "π";
}

bool Expression::isLeftBrace(const MyString &s) { return s == "(" || s == "["; }

bool Expression::isRightBrace(const MyString &s) { return s == ")" || s == "]"; }

bool Expression::isComma(const MyString &s) { return s == ","; }

bool Expression::isVariable(const MyString &s) {
  if (isFunction(s) || isConstant(s) || s[0] < 'a' || s[0] > 'z')
    return false;
  for (std::size_t i = 0; i < s.length(); i++) {
    if ((s[i] < '0' || s[i] > '9') && (s[i] < 'a' || s[i] > 'z'))
      return false;
  }
  return true;
}

int Expression::precedence(const MyString &s) {
  if (isFunction(s) || isUnaryOperator(s))
    return 10;
  if (s == "+" || s == "-")
    return 2;
  if (s == "*" || s == "/")
    return 3;
  if (s == "^")
    return 4;
  return -1;
}

Expression::BraceType Expression::braceType(const MyString &s) {
  if (s == "(" || s == ")")
    return BraceType_Round;
  if (s == "[" || s == "]")
    return BraceType_Square;
  failNotABrace(s);
  return BraceType_Unknown;
}

Expression::Associativity Expression::associativity(const MyString &s) {
  if (s == "+" || s == "-" || s == "*" || s == "/")
    return Associativity_Left;
  if (s == "^")
    return Associativity_Right;
  failNotABinaryOperator(s);
  return Associativity_Unknown;
}

Expression::ResultType Expression::getConstant(const MyString &s) {
  if (s == "e")
    return Math::Euler;
  if (s == "pi" || s == "π")
    return Math::Pi;
  failNotAConstant(s);
  return Expression::ResultType();
}

Expression::ResultType Expression::doUnaryOperation(const MyString &s,
                                                    Expression::ResultType a) {
  if (s == "~")
    return -a;
  if (s == "sin")
    return Math::sin(a);
  if (s == "cos")
    return Math::cos(a);
  if (s == "exp")
    return Math::exp(a);
  if (s == "abs")
    return Math::abs(a);
  if (s == "sqrt")
    return Math::sqrt(a);
  if (s == "cbrt")
    return Math::cbrt(a);
  failNotAnUnaryOperator(s);
  return Expression::ResultType();
}

Expression::ResultType Expression::doBinaryOperation(const MyString &s,
                                                     Expression::ResultType a,
                                                     Expression::ResultType b) {
  if (s == "+")
    return a + b;
  if (s == "-")
    return a - b;
  if (s == "*")
    return a * b;
  if (s == "/")
    return a / b;
  if (s == "^" || s == "pow")
    return Math::pow(a, b);
  if (s == "log")
    return Math::log(a, b);
  if (s == "min")
    return Math::min(a, b);
  if (s == "max")
    return Math::max(a, b);
  failNotABinaryOperator(s);
  return Expression::ResultType();
}

Expression::ResultType Expression::parseNumber(const MyString &s) {
  if (s.isEmpty())
    return 0;
  bool flagDot = false, flagExp = false, numNegative = false,
       expNegative = false;
  long long number = 0, dotPos = 0, exponent = 0, multiplier = 1;
  for (std::size_t i = 0; i < s.length(); i++) {
    if (s[i] == '.') {
      if (i == 0 || flagExp || flagDot)
        failNotANumber(s);
      flagDot = true;
    } else if (s[i] == 'e') {
      if (i == 0 || flagExp)
        failNotANumber(s);
      flagExp = true;
    } else if (s[i] == '-') {
      if (i == 0) {
        numNegative = true;
      } else if (s[i - 1] == 'e') {
        expNegative = true;
      } else {
        failNotANumber(s);
      }
    } else if (s[i] == '+') {
      if (i != 0 && s[i - 1] != 'e')
        failNotANumber(s);
    } else if (s[i] >= '0' && s[i] <= '9') {
      if (flagDot && !flagExp)
        dotPos++;
      if (flagExp) {
        exponent = (exponent * 10) + s[i] - '0';
      } else {
        number = (number * 10) + s[i] - '0';
      }
    } else {
      failNotANumber(s);
    }
  }
  if (numNegative)
    number = -number;
  if (expNegative) {
    exponent += dotPos;
  } else {
    exponent -= dotPos;
  }
  if (exponent < 0) {
    exponent = -exponent;
    expNegative = !expNegative;
  }
  multiplier <<= exponent;
  while (exponent--) {
    multiplier += multiplier << 2;
  }
  if (expNegative) {
    return static_cast<ResultType>(number) / multiplier;
  } else {
    return static_cast<ResultType>(number) * multiplier;
  }
}

void Expression::failWrongToken(const MyString &s) {
  throw std::invalid_argument("wrong token");
}

void Expression::failNotANumber(const MyString &s) {
  throw std::invalid_argument("not a number");
}

void Expression::failNotABrace(const MyString &s) {
  throw std::invalid_argument("not a brace");
}

void Expression::failNotAConstant(const MyString &s) {
  throw std::invalid_argument("not a constant");
}

void Expression::failNotAnUnaryOperator(const MyString &s) {
  throw std::invalid_argument("not an unary operator");
}

void Expression::failNotABinaryOperator(const MyString &s) {
  throw std::invalid_argument("not a binary operator");
}

void Expression::failWrongAssociativity(const MyString &s) {
  throw std::invalid_argument("unknown associativity");
}

void Expression::failWrongBraceType(const MyString &s) {
  throw std::invalid_argument("wrong brace type");
}

void Expression::failMissingLeftBrace() {
  throw std::invalid_argument("missing left brace");
}

void Expression::failMissingRightBrace() {
  throw std::invalid_argument("missing right brace");
}

void Expression::failMissingOperand() {
  throw std::invalid_argument("missing operand");
}

void Expression::failMissingOperator() {
  throw std::invalid_argument("missing operator");
}
