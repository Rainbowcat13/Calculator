#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "HashMap.h"
#include "List.h"
#include "Number.h"
#include "Queue.h"
#include "String.h"

class Expression {
public:
  enum BraceType { BraceType_Round, BraceType_Square, BraceType_Unknown };
  enum Associativity {
    Associativity_Left,
    Associativity_Right,
    Associativity_Unknown
  };
  explicit Expression(Queue<String>);
  Expression(const Expression &);
  Number evaluate() const;
  Queue<String> getPostfix() const;
  List<String> getVariablesNames() const;
  Number getVariable(String &) const;
  void setVariable(String &, Number);
  static bool isNumber(const String &);
  static bool isOperator(const String &);
  static bool isUnaryOperator(const String &);
  static bool isBinaryOperator(const String &);
  static bool isFunction(const String &);
  static bool isUnaryFunction(const String &);
  static bool isBinaryFunction(const String &);
  static bool isConstant(const String &);
  static bool isLeftBrace(const String &);
  static bool isRightBrace(const String &);
  static bool isComma(const String &);
  static bool isVariable(const String &);
  static int precedence(const String &);
  static BraceType braceType(const String &);
  static Associativity associativity(const String &);
  static Number getConstant(const String &);
  static Number doUnaryOperation(const String &, Number);
  static Number doBinaryOperation(const String &, Number, Number);
  static Number parseNumber(const String &);

private:
  Queue<String> postfix;
  HashMap<String, Number> variables;
  static void failWrongToken(const String &);
  static void failNotANumber(const String &);
  static void failNotAConstant(const String &);
  static void failNotABrace(const String &);
  static void failNotAnUnaryOperator(const String &);
  static void failNotABinaryOperator(const String &);
  static void failWrongAssociativity(const String &);
  static void failWrongBraceType(const String &);
  static void failMissingLeftBrace();
  static void failMissingRightBrace();
  static void failMissingOperand();
  static void failMissingOperator();
};

#endif
