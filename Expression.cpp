#include "Expression.h"
#include "Stack.h"
#include "Math.h"
#include <stdexcept>

Expression::Expression(Queue<String> q) {
  // TODO: Expression::Expression(Queue<String>) error handling
  Stack<String> s;
  s.push(String("("));
  q.push(String(")"));
  String prev(s.top());
  while (!q.isEmpty()) {
    String v = q.pop();
    if (isNumber(v)) {
      postfix.push(v);
    } else if (isOperator(v)) {
      if (v == "-" && (isOperator(prev) || isLeftBrace(prev) || isComma(prev))) {
        v = "~";
      }
      if (!isUnaryOperator(v)) {
        if (associativity(v) == RIGHT) {
          while (precedence(v) < precedence(s.top())) {
            postfix.push(s.pop());
          }
        } else {
          while (precedence(v) <= precedence(s.top())) {
            postfix.push(s.pop());
          }
        }
      }
      s.push(v);
    } else if (isLeftBrace(v)) {
      s.push(v);
    } else if (isRightBrace(v)) {
      while (!isLeftBrace(s.top())) {
        postfix.push(s.pop());
      }
      s.pop();
    } else if (isFunction(v)) {
      s.push(v);
    } else if (isComma(v)) {
      while (!isLeftBrace(s.top())) {
        postfix.push(s.pop());
      }
    } else {
      if (!isConstant(v)) {
        variables[v] = 0;
      }
      postfix.push(v);
    }
    prev = v;
  }
}

Expression::Expression(const Expression &e) {
  postfix = e.postfix;
}

Expression::ResultType Expression::evaluate() const {
  // TODO: Expression::evaluate() error handling
  Queue<String> q = postfix;
  Stack<ResultType> s;
  while (!q.isEmpty()) {
    String v = q.pop();
    if (isNumber(v)) {
      s.push(parseNumber(v));
    } else if (isConstant(v)) {
      s.push(getConstant(v));
    } else if (isVariable(v)) {
      s.push(getVariable(v));
    } else {
      if (isBinaryOperator(v)) {
        ResultType b = s.pop(), a = s.pop();
        s.push(doBinaryOperation(v, a, b));
      } else {
        ResultType a = s.pop();
        s.push(doUnaryOperation(v, a));
      }
    }
  }
  return s.pop();
}

Queue<String> Expression::getPostfix() const {
  return postfix;
}

Queue<String> Expression::getVariablesNames() const {
  // TODO: implement Expression::getVariableNames()
  return Queue<String>();
}

Expression::ResultType Expression::getVariable(String &s) const {
  return variables.get(s);
}

void Expression::setVariable(String &s, Expression::ResultType value) {
  variables[s] = value;
}

bool Expression::isNumber(const String &s) {
  bool dot = false, exp = false, result = true;
  for (unsigned int i = 0; i < s.length(); i++) {
    if (!dot && s[i] == '.') {
      dot = true;
    } else if (!exp && s[i] == 'e') {
      exp = true;
    } else if (i > 0 && s[i - 1] == 'e' && (s[i] == '-' || s[i] == '+')) {
      continue;
    } else if (s[i] >= '0' && s[i] <= '9') {
      continue;
    } else {
      result = false;
      break;
    }
  }
  return result;
}

bool Expression::isOperator(const String &s) {
  return isUnaryOperator(s) || isBinaryOperator(s);
}

bool Expression::isUnaryOperator(const String &s) {
  return s == "~";
}

bool Expression::isBinaryOperator(const String &s) {
  return s == "+" || s == "-" || s == "*" || s == "/" || s == "^";
}

bool Expression::isFunction(const String &s) {
  return isUnaryFunction(s) || isBinaryFunction(s);
}

bool Expression::isUnaryFunction(const String &s) {
  return s == "sin" || s == "cos" || s == "exp" || s == "abs" || s == "sqrt" || s == "cbrt";
}

bool Expression::isBinaryFunction(const String &s) {
  return s == "log" || s == "min" || s == "max";
}

bool Expression::isConstant(const String &s) {
  return s == "e" || s == "pi" || s == "π";
}

bool Expression::isLeftBrace(const String &s) {
  return s == "(" || s == "[";
}

bool Expression::isRightBrace(const String &s) {
  return s == ")" || s == "]";
}

bool Expression::isComma(const String &s) {
  return s == ",";
}

bool Expression::isVariable(const String &s) {
  if (isFunction(s) || isConstant(s) || s[0] < 'a' || s[0] > 'z') return false;
  for (unsigned int i = 0; i < s.length(); i++) {
    if ((s[i] < '0' || s[i] > '9') && (s[i] < 'a' || s[i] > 'z')) 
      return false;
  }
  return true;
}

int Expression::precedence(const String &s) {
  if (isFunction(s) || isUnaryOperator(s)) return 10;
  if (s == "+" || s == "-") return 2;
  if (s == "*" || s == "/") return 3;
  if (s == "^") return 4;
  return -1;
}

Expression::BraceType Expression::braceType(const String &s) {
  if (s == "(" || s == ")") return ROUND;
  if (s == "[" || s == "]") return SQUARE;
  throw std::invalid_argument("not a brace");
}

Expression::Associativity Expression::associativity(const String &s) {
  if (s == "+" || s == "-" || s == "*" || s == "/") return LEFT;
  if (s == "^") return RIGHT;
  throw std::invalid_argument("not a binary operator");
}

Expression::ResultType Expression::getConstant(const String &s) {
  if (s == "e") return 2.7182818284590452;
  if (s == "pi" || s == "π") return 3.1415926535897932;
  throw std::invalid_argument("not a constant");
}

Expression::ResultType Expression::doUnaryOperation(const String &s, Expression::ResultType a) {
  if (s == "~") return -a;
  if (s == "sin") return Math::sin(a);
  if (s == "cos") return Math::cos(a);
  if (s == "exp") return Math::exp(a);
  if (s == "abs") return Math::abs(a);
  if (s == "sqrt") return Math::sqrt(a);
  if (s == "cbrt") return Math::cbrt(a);
  throw std::invalid_argument("not an unary operation");
}

Expression::ResultType Expression::doBinaryOperation(const String &s, Expression::ResultType a, Expression::ResultType b) {
  if (s == "+") return a + b;
  if (s == "-") return a - b;
  if (s == "*") return a * b;
  if (s == "/") return a / b;
  if (s == "^") return Math::pow(a, b);
  if (s == "log") return Math::log(a, b);
  if (s == "min") return Math::min(a , b);
  if (s == "max") return Math::max(a, b);
  throw std::invalid_argument("not a binary operation");
}

Expression::ResultType Expression::parseNumber(const String &s) {
  if (s.isEmpty()) return 0;
  bool flagDot = false, flagExp = false, numNegative = false, expNegative = false;
  long long number = 0, dotPos = 0, exponent = 0, multiplier = 1;
  for (unsigned int i = 0; i < s.length(); i++) {
    if (s[i] == '.') {
      if (flagExp || flagDot) throw std::invalid_argument("not a number");
      flagDot = true;
    } else if (s[i] == 'e') {
      if (flagExp) throw std::invalid_argument("not a number");
      flagExp = true;
    } else if (s[i] == '-') {
      if (i == 0) {
        numNegative = true;
      } else if (s[i - 1] == 'e') {
        expNegative = true;
      } else {
        throw std::invalid_argument("not a number");
      }
    } else if (s[i] == '+') {
      if (i != 0 && s[i - 1] != 'e') throw std::invalid_argument("not a number");
    } else if (s[i] >= '0' && s[i] <= '9') {
      if (flagDot && !flagExp) dotPos++;
      if (flagExp) {
        exponent = (exponent * 10) + s[i] - '0';
      } else {
        number = (number * 10) + s[i] - '0';
      }
    } else {
      throw std::invalid_argument("not a number");
    }
  }
  if (numNegative) number = -number;
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

