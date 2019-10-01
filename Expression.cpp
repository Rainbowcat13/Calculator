#include "Expression.h"
#include "Math.h"
#include "Stack.h"
#include <stdexcept>

Expression::Expression(Queue<std::string> q) {
  Stack<std::string> s;
  s.push(std::string("("));
  q.push(std::string(")"));
  bool possibleNegation = true, requireFnBraces = false;
  std::string v;
  while (!q.isEmpty()) {
    if (s.isEmpty())
      failMissingLeftBrace();
    v = q.pop();
    if (v == "-" && possibleNegation)
      v = "~";
    if (Number::isNumber(v) || isConstant(v)) {
      postfix.push(v);
      possibleNegation = false;
    } else if (isVariable(v)) {
      variables[v] = Number();
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
      if (getAssocType(v) == AssocType_Right) {
        while (getPrecedence(v) < getPrecedence(s.top())) {
          postfix.push(s.pop());
        }
      } else if (getAssocType(v) == AssocType_Left) {
        while (getPrecedence(v) <= getPrecedence(s.top())) {
          postfix.push(s.pop());
        }
      } else {
        failWrongAssociativity(v);
      }
      s.push(v);
      possibleNegation = true;
    } else if (isLeftBrace(v)) {
      if (requireFnBraces && getBraceType(v) != BraceType_Round)
        failWrongBraceType(v);
      s.push(v);
      possibleNegation = true;
      requireFnBraces = false;
    } else if (isRightBrace(v)) {
      while (!isLeftBrace(s.top())) {
        postfix.push(s.pop());
      }
      if (getBraceType(v) != getBraceType(s.top()))
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

Number Expression::evaluate() const {
  if (postfix.isEmpty())
    return Number(0);
  Queue<std::string> q = postfix;
  Stack<Number> s;
  std::string v;
  Number a, b;
  while (!q.isEmpty()) {
    v = q.pop();
    if (Number::isNumber(v)) {
      s.push(Number::parseNumber(v));
    } else if (isConstant(v)) {
      s.push(getConstant(v));
    } else if (isVariable(v)) {
      s.push(getVariable(v));
    } else if (isBinaryOperator(v) || isBinaryFunction(v)) {
      if (s.isEmpty())
        failMissingOperand();
      b = s.pop();
      if (s.isEmpty())
        failMissingOperand();
      a = s.pop();
      s.push(doBinaryOperation(v, a, b));
    } else if (isUnaryOperator(v) || isUnaryFunction(v)) {
      if (s.isEmpty())
        failMissingOperand();
      a = s.pop();
      s.push(doUnaryOperation(v, a));
    } else {
      failWrongToken(v);
    }
  }
  a = s.pop();
  if (!s.isEmpty())
    failMissingOperator();
  return a;
}

Queue<std::string> Expression::getPostfix() const { return postfix; }

List<std::string> Expression::getVariablesNames() const { return variables.keys(); }

Number Expression::getVariable(std::string &s) const { return variables[s]; }

void Expression::setVariable(std::string &s, Number value) { variables[s] = value; }

bool Expression::isOperator(const std::string &s) {
  return isUnaryOperator(s) || isBinaryOperator(s);
}

bool Expression::isUnaryOperator(const std::string &s) { return s == "~"; }

bool Expression::isBinaryOperator(const std::string &s) {
  return s == "+" || s == "-" || s == "*" || s == "/" || s == "^";
}

bool Expression::isFunction(const std::string &s) {
  return isUnaryFunction(s) || isBinaryFunction(s);
}

bool Expression::isUnaryFunction(const std::string &s) {
  return s == "sin" || s == "cos" || s == "exp" || s == "abs" || s == "sqrt" ||
         s == "cbrt";
}

bool Expression::isBinaryFunction(const std::string &s) {
  return s == "pow" || s == "log" || s == "min" || s == "max";
}

bool Expression::isConstant(const std::string &s) {
  return s == "e" || s == "pi" || s == "π";
}

bool Expression::isLeftBrace(const std::string &s) { return s == "(" || s == "["; }

bool Expression::isRightBrace(const std::string &s) { return s == ")" || s == "]"; }

bool Expression::isComma(const std::string &s) { return s == ","; }

bool Expression::isVariable(const std::string &s) {
  if (isFunction(s) || isConstant(s) || s[0] < 'a' || s[0] > 'z')
    return false;
  for (std::size_t i = 0; i < s.length(); i++) {
    if ((s[i] < '0' || s[i] > '9') && (s[i] < 'a' || s[i] > 'z'))
      return false;
  }
  return true;
}

int Expression::getPrecedence(const std::string &s) {
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

Expression::BraceType Expression::getBraceType(const std::string &s) {
  if (s == "(" || s == ")")
    return BraceType_Round;
  if (s == "[" || s == "]")
    return BraceType_Square;
  failNotABrace(s);
  return BraceType_Unknown;
}

Expression::AssocType Expression::getAssocType(const std::string &s) {
  if (s == "+" || s == "-" || s == "*" || s == "/")
    return AssocType_Left;
  if (s == "^")
    return AssocType_Right;
  failNotABinaryOperator(s);
  return AssocType_Unknown;
}

Number Expression::getConstant(const std::string &s) {
  if (s == "e")
    return Math::euler();
  if (s == "pi" || s == "π")
    return Math::pi();
  failNotAConstant(s);
  return Number();
}

Number Expression::doUnaryOperation(const std::string &s, Number a) {
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
  return Number();
}

Number Expression::doBinaryOperation(const std::string &s, Number a, Number b) {
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
  return Number();
}

void Expression::failWrongToken(const std::string &s) {
  std::string msg = "wrong token: ";
  throw std::invalid_argument(msg + s);
}

void Expression::failNotANumber(const std::string &s) {
  std::string msg = "not a number: ";
  throw std::invalid_argument(msg + s);
}

void Expression::failNotABrace(const std::string &s) {
  std::string msg = "not a brace: ";
  throw std::invalid_argument(msg + s);
}

void Expression::failNotAConstant(const std::string &s) {
  std::string msg = "not a constant: ";
  throw std::invalid_argument(msg + s);
}

void Expression::failNotAnUnaryOperator(const std::string &s) {
  std::string msg = "not an unary operator: ";
  throw std::invalid_argument(msg + s);
}

void Expression::failNotABinaryOperator(const std::string &s) {
  std::string msg = "not a binary operator: ";
  throw std::invalid_argument(msg + s);
}

void Expression::failWrongAssociativity(const std::string &s) {
  failNotABinaryOperator(s);
}

void Expression::failWrongBraceType(const std::string &s) {
  std::string msg = "wrong brace type: ";
  throw std::invalid_argument(msg + s);
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
