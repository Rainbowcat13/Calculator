#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Queue.h"
#include "String.h"
#include "HashMap.h"

class Expression {
  public:
    using ResultType = double;
    enum BraceType { ROUND, SQUARE };
    enum Associativity { LEFT, RIGHT };
    explicit Expression(Queue<String>);
    Expression(const Expression &);
    ResultType evaluate() const;
    Queue<String> getPostfix() const;
    Queue<String> getVariablesNames() const;
    ResultType getVariable(String &) const;
    void setVariable(String&, ResultType);
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
    static ResultType getConstant(const String &);
    static ResultType doUnaryOperation(const String &, ResultType);
    static ResultType doBinaryOperation(const String &, ResultType, ResultType);
    static ResultType parseNumber(const String &);
  private:
    Queue<String> postfix;
    HashMap<String, ResultType> variables;
};

#endif

