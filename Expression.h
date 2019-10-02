#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "HashMap.h"
#include "List.h"
#include "Queue.h"
#include "mystring.h"

class Expression {
public:
  using ResultType = double;
  enum BraceType { BraceType_Round, BraceType_Square, BraceType_Unknown };
  enum Associativity {
    Associativity_Left,
    Associativity_Right,
    Associativity_Unknown
  };
  explicit Expression(Queue<MyString>);
  Expression(const Expression &);
  ResultType evaluate() const;
  Queue<MyString> getPostfix() const;
  List<MyString> getVariablesNames() const;
  ResultType getVariable(MyString &) const;
  void setVariable(MyString &, ResultType);
  static bool isNumber(const MyString &);
  static bool isOperator(const MyString &);
  static bool isUnaryOperator(const MyString &);
  static bool isBinaryOperator(const MyString &);
  static bool isFunction(const MyString &);
  static bool isUnaryFunction(const MyString &);
  static bool isBinaryFunction(const MyString &);
  static bool isConstant(const MyString &);
  static bool isLeftBrace(const MyString &);
  static bool isRightBrace(const MyString &);
  static bool isComma(const MyString &);
  static bool isVariable(const MyString &);
  static int precedence(const MyString &);
  static BraceType braceType(const MyString &);
  static Associativity associativity(const MyString &);
  static ResultType getConstant(const MyString &);
  static ResultType doUnaryOperation(const MyString &, ResultType);
  static ResultType doBinaryOperation(const MyString &, ResultType, ResultType);
  static ResultType parseNumber(const MyString &);

private:
  Queue<MyString> postfix;
  HashMap<MyString, ResultType> variables;
  static void failWrongToken(const MyString &);
  static void failNotANumber(const MyString &);
  static void failNotAConstant(const MyString &);
  static void failNotABrace(const MyString &);
  static void failNotAnUnaryOperator(const MyString &);
  static void failNotABinaryOperator(const MyString &);
  static void failWrongAssociativity(const MyString &);
  static void failWrongBraceType(const MyString &);
  static void failMissingLeftBrace();
  static void failMissingRightBrace();
  static void failMissingOperand();
  static void failMissingOperator();
};

#endif
