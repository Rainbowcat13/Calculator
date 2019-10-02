<<<<<<< HEAD
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
=======
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "HashMap.h"
#include "List.h"
#include "Number.h"
#include "Queue.h"
#include <string>

class Expression {
public:
  enum BraceType { BraceType_Round, BraceType_Square, BraceType_Unknown };
  enum AssocType { AssocType_Left, AssocType_Right, AssocType_Unknown };
  explicit Expression(Queue<std::string>);
  Expression(const Expression &);
  Number evaluate() const;
  Queue<std::string> getPostfix() const;
  List<std::string> getVariablesNames() const;
  Number getVariable(std::string &) const;
  void setVariable(std::string &, Number);
  static bool isNumber(const std::string &);
  static bool isOperator(const std::string &);
  static bool isUnaryOperator(const std::string &);
  static bool isBinaryOperator(const std::string &);
  static bool isFunction(const std::string &);
  static bool isUnaryFunction(const std::string &);
  static bool isBinaryFunction(const std::string &);
  static bool isConstant(const std::string &);
  static bool isLeftBrace(const std::string &);
  static bool isRightBrace(const std::string &);
  static bool isComma(const std::string &);
  static bool isVariable(const std::string &);
  static int getPrecedence(const std::string &);
  static BraceType getBraceType(const std::string &);
  static AssocType getAssocType(const std::string &);
  static Number getConstant(const std::string &);
  static Number doUnaryOperation(const std::string &, Number);
  static Number doBinaryOperation(const std::string &, Number, Number);

private:
  Queue<std::string> postfix;
  HashMap<std::string, Number> variables;
  static void failWrongToken(const std::string &);
  static void failNotANumber(const std::string &);
  static void failNotAConstant(const std::string &);
  static void failNotABrace(const std::string &);
  static void failNotAnUnaryOperator(const std::string &);
  static void failNotABinaryOperator(const std::string &);
  static void failWrongAssociativity(const std::string &);
  static void failWrongBraceType(const std::string &);
  static void failMissingLeftBrace();
  static void failMissingRightBrace();
  static void failMissingOperand();
  static void failMissingOperator();
};

#endif
>>>>>>> cc4f7a71590d8d6f35516dc65ef1573b9b2a42e3
