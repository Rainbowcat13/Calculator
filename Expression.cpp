#include "Expression.h"
#include "Math.h"
#include "Stack.h"
#include <stdexcept>

Expression::Expression(Queue<String> q) {
  Stack<String> s;
  s.push(String("("));
  q.push(String(")"));
  bool possibleNegation = true, requireFnBraces = false;
  String v;
  while (!q.isEmpty()) {
    if (s.isEmpty())
      failMissingLeftBrace();
    v = q.pop();
    if (v == "-" && possibleNegation)
      v = "~";
    if (isNumber(v) || isConstant(v)) {
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

Number Expression::evaluate() const {
  if (postfix.isEmpty())
    return Number(0);
  Queue<String> q = postfix;
  Stack<Number> s;
  String v;
  Number a, b;
  while (!q.isEmpty()) {
    v = q.pop();
    if (isNumber(v)) {
      s.push(parseNumber(v));
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

Queue<String> Expression::getPostfix() const { return postfix; }

List<String> Expression::getVariablesNames() const { return variables.keys(); }

Number Expression::getVariable(String &s) const { return variables[s]; }

void Expression::setVariable(String &s, Number value) { variables[s] = value; }

bool Expression::isNumber(const String &s) {
  if (s.isEmpty())
    return false;
  int n = s.length(), numSignPos = -1, dotPos = -1, expPos = -1;
  for (int i = 0; i < n; i++) {
    if (s[i] == '.' && i != n - 1 && i > 0 && expPos == -1 && dotPos == -1 &&
        numSignPos != i - 1) {
      dotPos = i;
    } else if (s[i] == 'e' && i != n - 1 && i > 0 && expPos == -1 &&
               dotPos != i - 1 && numSignPos != i - 1) {
      expPos = i;
    } else if ((s[i] == '-' || s[i] == '+') && i != n - 1 && i == 0) {
      numSignPos = i;
    } else if ((s[i] == '-' || s[i] == '+') && i != n - 1 && i > 0 &&
               expPos == i - 1) {
      continue;
    } else if (s[i] >= '0' && s[i] <= '9') {
      continue;
    } else {
      return false;
    }
  }
  return true;
}

bool Expression::isOperator(const String &s) {
  return isUnaryOperator(s) || isBinaryOperator(s);
}

bool Expression::isUnaryOperator(const String &s) { return s == "~"; }

bool Expression::isBinaryOperator(const String &s) {
  return s == "+" || s == "-" || s == "*" || s == "/" || s == "^";
}

bool Expression::isFunction(const String &s) {
  return isUnaryFunction(s) || isBinaryFunction(s);
}

bool Expression::isUnaryFunction(const String &s) {
  return s == "sin" || s == "cos" || s == "exp" || s == "abs" || s == "sqrt" ||
         s == "cbrt";
}

bool Expression::isBinaryFunction(const String &s) {
  return s == "pow" || s == "log" || s == "min" || s == "max";
}

bool Expression::isConstant(const String &s) {
  return s == "e" || s == "pi" || s == "π";
}

bool Expression::isLeftBrace(const String &s) { return s == "(" || s == "["; }

bool Expression::isRightBrace(const String &s) { return s == ")" || s == "]"; }

bool Expression::isComma(const String &s) { return s == ","; }

bool Expression::isVariable(const String &s) {
  if (isFunction(s) || isConstant(s) || s[0] < 'a' || s[0] > 'z')
    return false;
  for (std::size_t i = 0; i < s.length(); i++) {
    if ((s[i] < '0' || s[i] > '9') && (s[i] < 'a' || s[i] > 'z'))
      return false;
  }
  return true;
}

int Expression::precedence(const String &s) {
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

Expression::BraceType Expression::braceType(const String &s) {
  if (s == "(" || s == ")")
    return BraceType_Round;
  if (s == "[" || s == "]")
    return BraceType_Square;
  failNotABrace(s);
  return BraceType_Unknown;
}

Expression::Associativity Expression::associativity(const String &s) {
  if (s == "+" || s == "-" || s == "*" || s == "/")
    return Associativity_Left;
  if (s == "^")
    return Associativity_Right;
  failNotABinaryOperator(s);
  return Associativity_Unknown;
}

Number Expression::getConstant(const String &s) {
  if (s == "e")
    return Math::euler();
  if (s == "pi" || s == "π")
    return Math::pi();
  failNotAConstant(s);
  return Number();
}

Number Expression::doUnaryOperation(const String &s, Number a) {
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

Number Expression::doBinaryOperation(const String &s, Number a, Number b) {
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

Number Expression::parseNumber(const String &s) {
  if (s.isEmpty())
    failNotANumber(s);
  bool numSign = true, expSign = true;
  int n = s.length(), numSignPos = -1, fracEndPos = -1, dotPos = -1,
      expPos = -1;
  Number::Integral num = 0, exp = 0, mul = 1;
  for (int i = 0; i < n; i++) {
    if (s[i] == '.' && i != n - 1 && i > 0 && expPos == -1 && dotPos == -1 &&
        numSignPos != i - 1) {
      dotPos = i;
    } else if (s[i] == 'e' && i != n - 1 && i > 0 && expPos == -1 &&
               dotPos != i - 1 && numSignPos != i - 1) {
      expPos = i;
    } else if ((s[i] == '-' || s[i] == '+') && i != n - 1 && i == 0) {
      numSignPos = i;
      numSign = (s[i] == '+');
    } else if ((s[i] == '-' || s[i] == '+') && i != n - 1 && i > 0 &&
               expPos == i - 1) {
      expSign = (s[i] == '+');
    } else if (s[i] >= '0' && s[i] <= '9') {
      if (expPos != -1 && i > expPos) {
        exp = exp * 10 + s[i] - '0';
      } else if (dotPos != -1 && i > dotPos) {
        num = num * 10 + s[i] - '0';
        fracEndPos = i;
      } else {
        num = num * 10 + s[i] - '0';
      }
    } else {
      failNotANumber(s);
    }
  }
  if (!numSign)
    num = -num;
  if (expSign)
    exp -= fracEndPos - dotPos;
  else
    exp += fracEndPos - dotPos;
  if (exp < 0) {
    exp = -exp;
    expSign = !expSign;
  }
  mul <<= exp;
  while (exp--)
    mul += mul << 2;
  if (expSign)
    return Number(num * mul);
  else
    return Number(static_cast<Number::FloatingPoint>(num) / mul);
}

void Expression::failWrongToken(const String &s) {
  String msg = "wrong token: ";
  throw std::invalid_argument((msg + s).data());
}

void Expression::failNotANumber(const String &s) {
  String msg = "not a number: ";
  throw std::invalid_argument((msg + s).data());
}

void Expression::failNotABrace(const String &s) {
  String msg = "not a brace: ";
  throw std::invalid_argument((msg + s).data());
}

void Expression::failNotAConstant(const String &s) {
  String msg = "not a constant: ";
  throw std::invalid_argument((msg + s).data());
}

void Expression::failNotAnUnaryOperator(const String &s) {
  String msg = "not an unary operator: ";
  throw std::invalid_argument((msg + s).data());
}

void Expression::failNotABinaryOperator(const String &s) {
  String msg = "not a binary operator: ";
  throw std::invalid_argument((msg + s).data());
}

void Expression::failWrongAssociativity(const String &s) {
  failNotABinaryOperator(s);
}

void Expression::failWrongBraceType(const String &s) {
  String msg = "wrong brace type: ";
  throw std::invalid_argument((msg + s).data());
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
